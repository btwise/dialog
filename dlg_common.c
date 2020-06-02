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

