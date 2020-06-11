#include <stdlib.h>
#include <gtk/gtk.h>

#define UNUSED(x) (void)(x)

enum dlg_options
{
  DLG_HELP = 'h',
  DLG_VERSION = 'v',
  DLG_CAPTION = 'c',
  DLG_TITLE = 't',
  DLG_POSITION = 'p',
  DLG_SIZE = 's',
  DLG_THEME ='T'
};

enum dlg_widgets
{
  DLG_MENU = 128,
  DLG_YESNO,
  DLG_LIST
};


typedef struct 
{
  char *caption;
  char *title;
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
int dlg_list_widget(dlg_params *running_params);
void dlg_set_css(dlg_params *running_params);
char *dlg_translate(char *string);
void display_running_params(dlg_params *running_params);
void dlg_window_set_caption(GtkWindow *w, dlg_params *running_params);
void dlg_window_move(GtkWindow *w, dlg_params *running_params);
void dlg_window_resize(GtkWindow *w, dlg_params *running_params);

