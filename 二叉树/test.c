/*
 * RK3588缓存一致性问题实际代码示例
 * 场景：CPU + GPU + RGA共同处理图像数据
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

// RK3588硬件模块接口
#include <rga/rga.h>           // RGA图像处理器
#include <libmali/mali.h>      // GPU接口
#include <linux/dma-buf.h>     // DMA缓冲区管理

/*
 * DMA内存管理结构
 */
typedef struct {
    void *virt_addr;           // 虚拟地址 (CPU访问用)
    unsigned long phys_addr;   // 物理地址 (硬件DMA用)
    int dma_fd;               // DMA缓冲区文件描述符
    size_t size;              // 缓冲区大小
} dma_buffer_t;

/*
 * 图像数据结构
 */
typedef struct {
    dma_buffer_t buffer;       // DMA缓冲区
    int width;                // 图像宽度
    int height;               // 图像高度
    int format;               // 像素格式 (YUV420, RGB888等)
} image_data_t;

/*
 * 分配DMA内存 (可缓存的)
 */
int allocate_dma_buffer(dma_buffer_t *buf, size_t size)
{
    int dma_heap_fd;
    struct dma_heap_allocation_data alloc_data;
    
    // 打开DMA堆设备
    dma_heap_fd = open("/dev/dma_heap/system", O_RDWR);
    if (dma_heap_fd < 0) {
        perror("Failed to open DMA heap");
        return -1;
    }
    
    // 分配DMA缓冲区
    alloc_data.len = size;
    alloc_data.fd_flags = O_RDWR | O_CLOEXEC;
    alloc_data.heap_flags = 0;  // 可缓存内存
    
    if (ioctl(dma_heap_fd, DMA_HEAP_IOCTL_ALLOC, &alloc_data) < 0) {
        perror("Failed to allocate DMA buffer");
        close(dma_heap_fd);
        return -1;
    }
    
    close(dma_heap_fd);
    
    // 映射到用户空间
    buf->virt_addr = mmap(NULL, size, PROT_READ | PROT_WRITE, 
                          MAP_SHARED, alloc_data.fd, 0);
    if (buf->virt_addr == MAP_FAILED) {
        perror("Failed to map DMA buffer");
        close(alloc_data.fd);
        return -1;
    }
    
    buf->dma_fd = alloc_data.fd;
    buf->size = size;
    
    // 获取物理地址 (用于硬件DMA)
    // 注意：实际实现需要通过驱动接口获取
    buf->phys_addr = get_physical_address(buf->virt_addr);
    
    printf("✅ 分配DMA缓冲区: 虚拟地址=0x%p, 物理地址=0x%lx, 大小=%zu\n",
           buf->virt_addr, buf->phys_addr, buf->size);
    
    return 0;
}

/*
 * 缓存管理函数
 */
void cache_flush(void *addr, size_t size)
{
    // 将CPU缓存中的数据强制写回DDR
    // ARM特定的缓存操作
    __builtin___clear_cache((char*)addr, (char*)addr + size);
    
    // 或者使用系统调用
    cacheflush((unsigned long)addr, (unsigned long)addr + size, DCACHE);
    
    printf("🔄 缓存刷新: 地址=0x%p, 大小=%zu\n", addr, size);
}

void cache_invalidate(void *addr, size_t size)
{
    // 使CPU缓存失效，强制从DDR重新读取
    // 需要内核支持的系统调用
    syscall(__NR_cacheflush, addr, size, ICACHE);
    
    printf("❌ 缓存失效: 地址=0x%p, 大小=%zu\n", addr, size);
}

/*
 * 错误示例：没有缓存管理的图像处理
 */
void buggy_image_processing(image_data_t *image)
{
    printf("\n=== ❌ 错误示例：没有缓存管理 ===\n");
    
    unsigned char *pixel_data = (unsigned char*)image->buffer.virt_addr;
    
    // 1. CPU修改图像数据 (增加亮度)
    printf("🖥️  CPU: 增加图像亮度...\n");
    for (int i = 0; i < image->width * image->height; i++) {
        pixel_data[i] = (pixel_data[i] < 200) ? pixel_data[i] + 55 : 255;
    }
    printf("🖥️  CPU: 亮度调整完成，数据在CPU缓存中\n");
    
    // 💥 问题：CPU修改的数据还在L1/L2缓存中，没有写回DDR！
    
    // 2. RGA进行图像缩放 (直接从DDR读取)
    printf("🔧 RGA: 开始图像缩放处理...\n");
    rga_info_t src_info, dst_info;
    
    // RGA源图像信息
    src_info.fd = image->buffer.dma_fd;
    src_info.mmuFlag = 1;
    src_info.rect.xoffset = 0;
    src_info.rect.yoffset = 0;
    src_info.rect.width = image->width;
    src_info.rect.height = image->height;
    src_info.format = RK_FORMAT_YCbCr_420_SP;
    
    // RGA会从DDR物理地址直接读取数据
    // 但是读到的是CPU修改前的旧数据！
    c_RkRgaBlit(&src_info, &dst_info, NULL);
    
    printf("🔧 RGA: 缩放完成，但处理的是旧数据！\n");
    printf("💥 结果：图像亮度调整丢失，出现数据不一致！\n");
}

/*
 * 正确示例：使用缓存管理的图像处理
 */
void correct_image_processing(image_data_t *image)
{
    printf("\n=== ✅ 正确示例：使用缓存管理 ===\n");
    
    unsigned char *pixel_data = (unsigned char*)image->buffer.virt_addr;
    
    // 1. CPU修改图像数据 (增加亮度)
    printf("🖥️  CPU: 增加图像亮度...\n");
    for (int i = 0; i < image->width * image->height; i++) {
        pixel_data[i] = (pixel_data[i] < 200) ? pixel_data[i] + 55 : 255;
    }
    printf("🖥️  CPU: 亮度调整完成\n");
    
    // ✅ 关键：在RGA访问前，刷新CPU缓存到DDR
    printf("🔄 刷新CPU缓存到DDR...\n");
    cache_flush(image->buffer.virt_addr, image->buffer.size);
    
    // 2. RGA进行图像缩放
    printf("🔧 RGA: 开始图像缩放处理...\n");
    rga_info_t src_info, dst_info;
    
    src_info.fd = image->buffer.dma_fd;
    // ... (配置参数同上)
    
    // 现在RGA从DDR读取到的是CPU修改后的最新数据
    c_RkRgaBlit(&src_info, &dst_info, NULL);
    
    printf("🔧 RGA: 缩放完成\n");
    
    // ✅ 关键：在CPU访问RGA处理结果前，使CPU缓存失效
    printf("❌ 使CPU缓存失效...\n");
    cache_invalidate(dst_info.virAddr, dst_info.size);
    
    // 3. CPU读取RGA处理后的结果
    printf("🖥️  CPU: 读取RGA处理结果...\n");
    unsigned char *result_data = (unsigned char*)dst_info.virAddr;
    // CPU现在能够读取到RGA的最新处理结果
    
    printf("✅ 结果：数据一致性保证，处理正确！\n");
}

/*
 * 复杂场景：CPU + GPU + RKVDEC协同工作
 */
void complex_multimedia_pipeline(void)
{
    printf("\n=== 🎬 复杂多媒体处理流水线 ===\n");
    
    // 分配DMA缓冲区
    image_data_t raw_frame, processed_frame, final_frame;
    allocate_dma_buffer(&raw_frame.buffer, 1920*1080*3/2);      // YUV420
    allocate_dma_buffer(&processed_frame.buffer, 1920*1080*4);   // RGBA
    allocate_dma_buffer(&final_frame.buffer, 1920*1080*4);      // RGBA
    
    // 1. RKVDEC硬件解码视频帧
    printf("\n📹 阶段1: RKVDEC解码视频帧\n");
    rkvdec_decode_frame(&raw_frame);
    printf("🔧 RKVDEC: 解码完成，YUV数据写入DDR\n");
    
    // ✅ RKVDEC绕过CPU缓存直接写DDR，CPU需要使缓存失效
    cache_invalidate(raw_frame.buffer.virt_addr, raw_frame.buffer.size);
    
    // 2. CPU进行图像分析 (人脸检测等)
    printf("\n🤖 阶段2: CPU进行AI分析\n");
    unsigned char *yuv_data = (unsigned char*)raw_frame.buffer.virt_addr;
    
    // CPU分析图像，检测人脸区域
    face_detection_result_t faces[10];
    int face_count = detect_faces(yuv_data, 1920, 1080, faces);
    printf("🖥️  CPU: 检测到 %d 个人脸\n", face_count);
    
    // CPU在图像上标记人脸边框
    draw_face_boxes(yuv_data, faces, face_count);
    printf("🖥️  CPU: 人脸边框标记完成\n");
    
    // ✅ CPU修改完成，刷新缓存到DDR
    cache_flush(raw_frame.buffer.virt_addr, raw_frame.buffer.size);
    
    // 3. RGA进行格式转换 (YUV → RGBA)
    printf("\n🎨 阶段3: RGA格式转换\n");
    rga_info_t rga_src, rga_dst;
    
    // 配置RGA源 (YUV with face boxes)
    rga_src.fd = raw_frame.buffer.dma_fd;
    rga_src.format = RK_FORMAT_YCbCr_420_SP;
    
    // 配置RGA目标 (RGBA)
    rga_dst.fd = processed_frame.buffer.dma_fd;
    rga_dst.format = RK_FORMAT_RGBA_8888;
    
    // RGA执行YUV到RGBA转换
    c_RkRgaBlit(&rga_src, &rga_dst, NULL);
    printf("🔧 RGA: YUV→RGBA转换完成\n");
    
    // ✅ RGA处理完成，CPU需要使缓存失效
    cache_invalidate(processed_frame.buffer.virt_addr, processed_frame.buffer.size);
    
    // 4. GPU进行特效渲染
    printf("\n🎮 阶段4: GPU特效渲染\n");
    
    // GPU渲染管线设置
    mali_surface_t gpu_src_surface, gpu_dst_surface;
    
    // 创建GPU表面 (从DMA缓冲区)
    gpu_src_surface.dma_fd = processed_frame.buffer.dma_fd;
    gpu_src_surface.format = MALI_FORMAT_RGBA8888;
    gpu_src_surface.width = 1920;
    gpu_src_surface.height = 1080;
    
    gpu_dst_surface.dma_fd = final_frame.buffer.dma_fd;
    gpu_dst_surface.format = MALI_FORMAT_RGBA8888;
    gpu_dst_surface.width = 1920;
    gpu_dst_surface.height = 1080;
    
    // GPU执行美颜特效渲染
    mali_render_beauty_effect(&gpu_src_surface, &gpu_dst_surface);
    printf("🔧 GPU: 美颜特效渲染完成\n");
    
    // ✅ GPU处理完成，CPU需要使缓存失效
    cache_invalidate(final_frame.buffer.virt_addr, final_frame.buffer.size);
    
    // 5. CPU进行最终后处理
    printf("\n📱 阶段5: CPU最终后处理\n");
    unsigned char *final_data = (unsigned char*)final_frame.buffer.virt_addr;
    
    // CPU添加水印、时间戳等
    add_watermark(final_data, 1920, 1080);
    add_timestamp(final_data, 1920, 1080);
    printf("🖥️  CPU: 水印和时间戳添加完成\n");
    
    // ✅ CPU最终修改，刷新缓存到DDR
    cache_flush(final_frame.buffer.virt_addr, final_frame.buffer.size);
    
    // 6. 显示输出
    printf("\n📺 阶段6: 显示输出\n");
    display_frame(&final_frame);
    printf("✅ 完整流水线处理完成，数据一致性保证！\n");
    
    // 清理资源
    free_dma_buffer(&raw_frame.buffer);
    free_dma_buffer(&processed_frame.buffer);
    free_dma_buffer(&final_frame.buffer);
}

/*
 * 性能对比：缓存 vs 非缓存内存
 */
void performance_comparison(void)
{
    printf("\n=== ⚡ 性能对比：缓存 vs 非缓存内存 ===\n");
    
    size_t buffer_size = 1920 * 1080 * 4;  // 4K RGBA图像
    
    // 1. 分配可缓存DMA内存
    dma_buffer_t cached_buffer;
    allocate_dma_buffer(&cached_buffer, buffer_size);
    
    // 2. 分配非缓存DMA内存
    dma_buffer_t uncached_buffer;
    allocate_uncached_dma_buffer(&uncached_buffer, buffer_size);
    
    clock_t start, end;
    
    // 测试1：CPU写入性能
    printf("\n📊 CPU写入性能测试:\n");
    
    start = clock();
    memset(cached_buffer.virt_addr, 0xFF, buffer_size);
    end = clock();
    double cached_write_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    
    start = clock();
    memset(uncached_buffer.virt_addr, 0xFF, buffer_size);
    end = clock();
    double uncached_write_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    
    printf("  可缓存内存写入:   %.2f ms\n", cached_write_time);
    printf("  非缓存内存写入:   %.2f ms\n", uncached_write_time);
    printf("  性能差异: %.1fx\n", uncached_write_time / cached_write_time);
    
    // 测试2：CPU读取性能
    printf("\n📊 CPU读取性能测试:\n");
    volatile int sum = 0;
    int *cached_data = (int*)cached_buffer.virt_addr;
    int *uncached_data = (int*)uncached_buffer.virt_addr;
    
    start = clock();
    for (int i = 0; i < buffer_size/4; i++) {
        sum += cached_data[i];
    }
    end = clock();
    double cached_read_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    
    start = clock();
    for (int i = 0; i < buffer_size/4; i++) {
        sum += uncached_data[i];
    }
    end = clock();
    double uncached_read_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    
    printf("  可缓存内存读取:   %.2f ms\n", cached_read_time);
    printf("  非缓存内存读取:   %.2f ms\n", uncached_read_time);
    printf("  性能差异: %.1fx\n", uncached_read_time / cached_read_time);
    
    printf("\n💡 结论:\n");
    printf("  ✅ 可缓存内存：CPU访问快，但需要缓存管理\n");
    printf("  ⚠️  非缓存内存：无缓存问题，但CPU访问慢10-100倍\n");
    printf("  🎯 推荐：CPU频繁访问时使用可缓存内存+缓存管理\n");
}

/*
 * 缓存管理最佳实践
 */
void cache_management_best_practices(void)
{
    printf("\n=== 📋 缓存管理最佳实践 ===\n");
    
    printf("🔧 何时使用缓存刷新 (Cache Flush):\n");
    printf("  ✅ CPU修改数据后，其他硬件要访问时\n");
    printf("  ✅ 示例：CPU处理图像 → RGA缩放\n");
    printf("  ✅ 示例：CPU准备顶点数据 → GPU渲染\n");
    
    printf("\n🔧 何时使用缓存失效 (Cache Invalidate):\n");
    printf("  ✅ 硬件修改数据后，CPU要访问时\n");
    printf("  ✅ 示例：RKVDEC解码 → CPU分析\n");
    printf("  ✅ 示例：GPU渲染完成 → CPU读取结果\n");
    
    printf("\n🔧 何时使用缓存同步 (Cache Sync):\n");
    printf("  ✅ CPU和硬件交替访问同一数据时\n");
    printf("  ✅ 示例：CPU-GPU协同渲染\n");
    printf("  ✅ 同时执行刷新和失效操作\n");
    
    printf("\n⚠️  常见错误:\n");
    printf("  ❌ 忘记在硬件访问前刷新CPU缓存\n");
    printf("  ❌ 忘记在CPU访问前使硬件缓存失效\n");
    printf("  ❌ 过度使用非缓存内存导致性能下降\n");
    printf("  ❌ 缓存操作的地址范围不正确\n");
    
    printf("\n💡 调试技巧:\n");
    printf("  🔍 使用内存填充模式检测缓存问题\n");
    printf("  🔍 在关键点打印数据内容进行对比\n");
    printf("  🔍 使用性能计数器监控缓存命中率\n");
    printf("  🔍 单独测试每个硬件模块的数据流\n");
}

/*
 * 实际应用场景示例
 */
void real_world_scenarios(void)
{
    printf("\n=== 🌍 实际应用场景 ===\n");
    
    printf("📱 智能手机相机应用:\n");
    printf("  摄像头 → ISP → CPU降噪 → GPU美颜 → CPU压缩 → 存储\n");
    printf("  关键：每个阶段间的缓存同步\n");
    
    printf("\n🚗 车载显示系统:\n");
    printf("  GPS数据 → CPU处理 → GPU渲染地图 → 显示控制器 → 屏幕\n");
    printf("  实时性要求高，缓存管理影响响应速度\n");
    
    printf("\n🏭 工业视觉检测:\n");
    printf("  工业相机 → FPGA预处理 → CPU缺陷检测 → GPU结果叠加 → 显示\n");
    printf("  精度要求高，缓存不一致会导致检测错误\n");
    
    printf("\n🎮 游戏主机:\n");
    printf("  CPU游戏逻辑 → GPU渲染 → 音频处理器 → HDMI输出\n");
    printf("  帧率稳定性要求高，缓存延迟影响游戏体验\n");
}

/*
 * 主函数：演示缓存一致性问题
 */
int main(int argc, char *argv[])
{
    printf("=== RK3588缓存一致性问题详细分析 ===\n");
    
    // 初始化硬件模块
    init_rga();
    init_mali_gpu();
    init_rkvdec();
    
    // 分配测试用的图像数据
    image_data_t test_image;
    test_image.width = 1920;
    test_image.height = 1080;
    test_image.format = IMAGE_FORMAT_YUV420;
    
    if (allocate_dma_buffer(&test_image.buffer, 
                           test_image.width * test_image.height * 3 / 2) < 0) {
        printf("❌ DMA缓冲区分配失败\n");
        return -1;
    }
    
    // 填充测试数据
    memset(test_image.buffer.virt_addr, 0x80, test_image.buffer.size);
    
    // 演示缓存一致性问题
    printf("\n" "=" * 60);
    buggy_image_processing(&test_image);
    
    printf("\n" "=" * 60);
    correct_image_processing(&test_image);
    
    // 复杂场景演示
    complex_multimedia_pipeline();
    
    // 性能对比
    performance_comparison();
    
    // 最佳实践
    cache_management_best_practices();
    
    // 实际应用场景
    real_world_scenarios();
    
    // 清理资源
    free_dma_buffer(&test_image.buffer);
    
    printf("\n✅ 缓存一致性分析完成！\n");
    printf("💡 记住：在多处理器系统中，缓存管理是数据正确性的关键！\n");
    
    return 0;
}