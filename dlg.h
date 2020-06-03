#include <stdlib.h>
#include <gtk/gtk.h>

#define UNUSED(x) (void)(x)

typedef struct 
{
  char *caption;
  char *css_filename;
  int posx;
  int posy;
  int width;
  int height;
  int first;
  int last;
  char **argv;
} dlg_params ;

int dlg_menu_widget(dlg_params *running_params);
int dlg_yesno_widget(dlg_params *running_params);
void dlg_set_css(dlg_params *running_params);
char *translate(char *string);
void dlg_window_set_caption(GtkWindow *w, dlg_params *running_params);
void dlg_window_move(GtkWindow *w, dlg_params *running_params);
void dlg_window_resize(GtkWindow *w, dlg_params *running_params);

