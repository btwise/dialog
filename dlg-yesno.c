#include <dlg.h>

int dlg_yesno_widget(dlg_params *running_params)
{
  int status = 0;
#define BUFSIZE 1024
  char title[BUFSIZE] = { 0 };
  while (running_params->first < running_params->last)
    g_strlcat(title, running_params->argv[running_params->first++], BUFSIZE);
  translate(title);
#undef BUFSIZE

	gtk_init(NULL, NULL);
  GtkWidget *box = gtk_message_dialog_new(0,
      GTK_DIALOG_MODAL,
      GTK_MESSAGE_QUESTION,
      GTK_BUTTONS_YES_NO,
      title
      );

  dlg_set_css(running_params);
  dlg_window_set_caption(GTK_WINDOW(box), running_params);
  dlg_window_move(GTK_WINDOW(box), running_params);
  dlg_window_resize(GTK_WINDOW(box), running_params);

  switch(gtk_dialog_run(GTK_DIALOG(box)))
  {
    case GTK_RESPONSE_YES:
      status = TRUE;
      break;
    default :
      status = FALSE;
      break;
  }
  gtk_widget_destroy(box);
  return(status);
}
