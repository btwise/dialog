#include <dlg.h>

static void st_action(GtkWidget *widget, gpointer user_data);
static void st_quit(GtkWidget *widget, gpointer user_data);

typedef struct _item
{
  char *label;
  char *action;
} item;

int dlg_menu_widget(dlg_params *running_params)
{
  item **items;

  const int nbitems = (running_params->last - running_params->first) / 2;
  if (nbitems)
  {
    items = malloc(sizeof(item *) * nbitems);
    for (int i = 0 ; i < nbitems ; i++)
    {
      items[i] = (item *)malloc(sizeof(item));
      items[i]->action = running_params->argv[running_params->first++];
      items[i]->label = running_params->argv[running_params->first++];
    } 
  }
  else return (0);

	gtk_init(NULL, NULL);
  GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(GTK_WIDGET(main_window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  //gtk_button_box_set_layout(GTK_BUTTON_BOX(button_box), GTK_BUTTONBOX_EXPAND);
	gtk_container_add(GTK_CONTAINER(main_window), button_box);

  dlg_set_css(running_params);
  dlg_window_set_caption(GTK_WINDOW(main_window), running_params);
  dlg_window_move(GTK_WINDOW(main_window), running_params);
  dlg_window_resize(GTK_WINDOW(main_window), running_params);

  for (int i = 0 ; i < nbitems ; i++)
  {
    GtkWidget *button = gtk_button_new_with_mnemonic(items[i]->label);
    GtkStyleContext *context = gtk_widget_get_style_context(button);
    gtk_style_context_add_class(context, "menu_button");
    gtk_box_pack_start(GTK_BOX(button_box), button , TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(st_action), items[i]);
  }

  // quit button
 	GtkWidget *button_quit = gtk_button_new_with_mnemonic ("_Quitter");
  GtkStyleContext *context = gtk_widget_get_style_context(button_quit);
  gtk_style_context_add_class(context, "menu_button");
  gtk_box_pack_start(GTK_BOX(button_box), button_quit, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button_quit), "clicked", G_CALLBACK(st_quit), main_window);

  gtk_widget_show_all(main_window);
  gtk_main(); // Start infinite loop

  return(1);
}

static void st_action(GtkWidget *widget, gpointer user_data)
{
  UNUSED(widget);
  item *it = user_data;
  puts(it->action);
  gtk_main_quit();
}

static void st_quit(GtkWidget *widget, gpointer user_data)
{
  UNUSED(widget);

  GtkWidget *w = gtk_message_dialog_new(user_data,
      GTK_DIALOG_MODAL,
      GTK_MESSAGE_QUESTION,
      GTK_BUTTONS_YES_NO,
      "Voulez vous vraiment\n"
      "quitter le programme?");

  switch(gtk_dialog_run(GTK_DIALOG(w)))
  {
    case GTK_RESPONSE_YES:
      gtk_main_quit();
      break;
    default:
      break;
  }
  gtk_widget_destroy(w);
}
