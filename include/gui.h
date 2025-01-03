#ifndef GUI_H
#define GUI_H

#ifdef __cplusplus
extern "C"
{
#endif

    void gui_init(void *window_ptr);
    void gui_new_frame();
    void gui_render();
    void gui_shutdown();

#ifdef __cplusplus
}
#endif

#endif
