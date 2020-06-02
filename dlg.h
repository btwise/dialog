#include <stdlib.h>
#include <gtk/gtk.h>

#define UNUSED(x) (void)(x)

typedef struct 
{
  char *caption;
  char *css_filename;
  int first;
  int last;
  char **argv;
} dlg_params ;

int dlg_menu_widget(dlg_params *running_params);
int dlg_yesno_widget(dlg_params *running_params);
void dlg_set_css(dlg_params *running_params);

