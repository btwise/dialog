#include <dlg.h>

int dlg_yesno_widget(dlg_params *running_params)
{
  const int nbargs = (running_params->last - running_params->first);
  int status = 0;
  #define BUFSIZE 1024
  char text[BUFSIZE] = { 0 };

  if (running_params->title)
  {
//    g_strlcat(text, running_params->title, BUFSIZE);
//   g_strlcat(text, "\n\n", BUFSIZE);
  }

  if (nbargs)
  {
    for (int i = 0 ; i < nbargs ; i++)
    {
      g_strlcat(text, running_params->argv[running_params->first++], BUFSIZE);
      g_strlcat(text, " ", BUFSIZE);
    }
    text[strlen(text) - 1] = '\0';
    dlg_translate(text);
  }
  else return (0);

	gtk_init(NULL, NULL);
  
  GtkWidget *main_window = gtk_message_dialog_new(0,
      GTK_DIALOG_MODAL,
      GTK_MESSAGE_QUESTION,
      GTK_BUTTONS_YES_NO,
      running_params->title ? running_params->title : text
      );
  if (running_params->title) gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(main_window), text);

  dlg_set_css(running_params);
  dlg_window_set_caption(GTK_WINDOW(main_window), running_params);
  dlg_window_move(GTK_WINDOW(main_window), running_params);
  dlg_window_resize(GTK_WINDOW(main_window), running_params);

  switch(gtk_dialog_run(GTK_DIALOG(main_window)))
  {
    case GTK_RESPONSE_YES:
      status = TRUE;
      break;
    default :
      status = FALSE;
      break;
  }
  gtk_widget_destroy(main_window);
  return(status);
}
