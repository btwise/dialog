#include <dlg.h>

void dlg_set_css(dlg_params *running_params)
{
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;

  if (running_params->css_filename)
  {
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_css_provider_load_from_file(GTK_CSS_PROVIDER(provider),
                g_file_new_for_commandline_arg(running_params->css_filename), NULL);
  }
}

char *dlg_translate(char *string)
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

void display_running_params(dlg_params *p)
{
  printf("     caption=%s\n", p->caption);
  printf("       title=%s\n", p->title);
  printf("css_filename=%s\n", p->css_filename);
  printf("        posx=%d\n", p->posx);
  printf("        posy=%d\n", p->posy);
  printf("       width=%d\n", p->width);
  printf("      height=%d\n", p->height);
  printf("       first=%d\n", p->first);
  printf("        last=%d\n", p->last);
  printf("        argv=%ld\n", (long int)p->argv);
}

void dlg_window_set_caption(GtkWindow *w, dlg_params *running_params)
{
  if (running_params->caption)
    gtk_window_set_title(GTK_WINDOW(w), running_params->caption);
}

void dlg_window_move(GtkWindow *w, dlg_params *running_params)
{
  if (running_params->posx > -1 && running_params->posy > -1)
    gtk_window_move(GTK_WINDOW(w), running_params->posx, running_params->posy);
}

void dlg_window_resize(GtkWindow *w, dlg_params *running_params)
{
  if (running_params->width > -1 && running_params->height > -1)
    gtk_window_set_default_size(GTK_WINDOW(w), running_params->width, running_params->height);
}
