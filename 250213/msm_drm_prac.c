#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <drm/drm.h>
#include <drm/drm_mode.h>

#define DRM_DEVICE "/dev/dri/card0"

int main() {
    int drm_fd = open(DRM_DEVICE, O_RDWR);
    if (drm_fd < 0) {
        perror("Failed to open DRM device");
        return EXIT_FAILURE;
    }

    // Get DRM resources
    struct drm_mode_card_res res = {0};
    if (ioctl(drm_fd, DRM_IOCTL_MODE_GETRESOURCES, &res) < 0) {
        perror("Failed to get DRM resources");
        close(drm_fd);
        return EXIT_FAILURE;
    }

    // Allocate memory for connectors, encoders, CRTCs, and FBs
    res.connector_id_ptr = (uintptr_t)malloc(res.count_connectors * sizeof(uint32_t));
    res.encoder_id_ptr = (uintptr_t)malloc(res.count_encoders * sizeof(uint32_t));
    res.crtc_id_ptr = (uintptr_t)malloc(res.count_crtcs * sizeof(uint32_t));
    res.fb_id_ptr = (uintptr_t)malloc(res.count_fbs * sizeof(uint32_t));

    if (ioctl(drm_fd, DRM_IOCTL_MODE_GETRESOURCES, &res) < 0) {
        perror("Failed to get DRM resources with buffer");
        close(drm_fd);
        return EXIT_FAILURE;
    }

    // Get information about the first connector
    uint32_t *connectors = (uint32_t *)res.connector_id_ptr;
    struct drm_mode_get_connector conn = {0};
    conn.connector_id = connectors[0];

    if (ioctl(drm_fd, DRM_IOCTL_MODE_GETCONNECTOR, &conn) < 0) {
        perror("Failed to get connector information");
        close(drm_fd);
        return EXIT_FAILURE;
    }

    // Get information about the first CRTC
    uint32_t *crtcs = (uint32_t *)res.crtc_id_ptr;
    struct drm_mode_crtc crtc = {0};
    crtc.crtc_id = crtcs[0];

    // Set display mode
    crtc.mode_valid = 1;
    crtc.fb_id = 0;
    crtc.x = 0;
    crtc.y = 0;
    crtc.gamma_size = 0;

    if (ioctl(drm_fd, DRM_IOCTL_MODE_SETCRTC, &crtc) < 0) {
        perror("Failed to set CRTC mode");
        close(drm_fd);
        return EXIT_FAILURE;
    }

    // Create framebuffer
    struct drm_mode_create_dumb create_dumb = {0};
    create_dumb.width = 1920;
    create_dumb.height = 1080;
    create_dumb.bpp = 32;

    if (ioctl(drm_fd, DRM_IOCTL_MODE_CREATE_DUMB, &create_dumb) < 0) {
        perror("Failed to create dumb framebuffer");
        close(drm_fd);
        return EXIT_FAILURE;
    }

    // Map framebuffer to user space
    struct drm_mode_map_dumb map_dumb = {0};
    map_dumb.handle = create_dumb.handle;

    if (ioctl(drm_fd, DRM_IOCTL_MODE_MAP_DUMB, &map_dumb) < 0) {
        perror("Failed to map dumb framebuffer");
        close(drm_fd);
        return EXIT_FAILURE;
    }

    void *fb_ptr = mmap(0, create_dumb.size, PROT_READ | PROT_WRITE, MAP_SHARED, drm_fd, map_dumb.offset);
    if (fb_ptr == MAP_FAILED) {
        perror("Failed to mmap framebuffer");
        close(drm_fd);
        return EXIT_FAILURE;
    }

    // Fill framebuffer with color (blue)
    memset(fb_ptr, 0xFF, create_dumb.size);

    printf("Display frame buffer filled with blue color\n");

    // Cleanup
    munmap(fb_ptr, create_dumb.size);
    close(drm_fd);
    free((void*)res.connector_id_ptr);
    free((void*)res.encoder_id_ptr);
    free((void*)res.crtc_id_ptr);
    free((void*)res.fb_id_ptr);

    printf("DRM display operation completed successfully\n");
    return EXIT_SUCCESS;
}

