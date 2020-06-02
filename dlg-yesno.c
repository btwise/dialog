#include <dlg.h>

static char *st_translate(char *string);

int dlg_yesno_widget(dlg_params *running_params)
{
  int status = 0;
  char *title = 0 ;
  while (running_params->first < running_params->last)
    title = g_strdup_printf("%s ", running_params->argv[running_params->first++]);
  title = st_translate(title);

	gtk_init(NULL, NULL);
  GtkWidget *box = gtk_message_dialog_new(0,
      GTK_DIALOG_MODAL,
      GTK_MESSAGE_QUESTION,
      GTK_BUTTONS_YES_NO,
      title
      );
  g_free(title);

  dlg_set_css(running_params);

  if (running_params->caption)
    gtk_window_set_title(GTK_WINDOW(box), running_params->caption);

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

static char *st_translate(char *string)
{
  char *here=string;
  size_t len=strlen(string);
  int num;
  int numlen;

  while (NULL != (here = strchr(here,'\\')))
  {
    numlen=1;
    switch (here[1])
    {
    case '\\':
          break;
    case 'r':
          *here = '\r';
          break;
    case 'n':
          *here = '\n';
          break;
    case 't':
          *here = '\t';
          break;
    case 'v':
          *here = '\v';
          break;
    case 'a':
          *here = '\a';
          break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
          numlen = sscanf(here,"%o",&num);
          *here = (char)num;
          break;
    case 'x':
          numlen = sscanf(here,"%x",&num);
          *here = (char) num;
          break;
    }
    num = here - string + numlen;
    here++;
    memmove(here, here + numlen, len - num);
  }
  return string;
}
