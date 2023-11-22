#ifndef RRX_H 
#define RRX_H

#ifdef __cplusplus
extern "C" {
#endif
void rrx_init();
void rrx_swapFramebuffer();
void rrx_GetDrawableSize(int* x, int* y);

#ifdef __cplusplus
}
#endif

#endif // RRX_H
