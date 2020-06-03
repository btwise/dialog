#include <dlg.h>

static void st_doAction(GtkWidget *widget, gpointer user_data);
static void st_doQuit(GtkWidget *widget, gpointer user_data);

typedef struct _item
{
  char *label;
  char *action;
  GtkWidget *button;
  struct _item *next;
} item;

int dlg_menu_widget(dlg_params *running_params)
{
  item *first_item, *current_item, *last_item;
  first_item =  current_item = last_item = 0 ;
  if (running_params->first < running_params->last)
    {
      while (running_params->first < running_params->last)
      {
        current_item = (item *)malloc(sizeof(item));
        current_item->action = running_params->argv[running_params->first++];
        current_item->label = running_params->argv[running_params->first++];
        current_item->next = 0;

        if (!first_item)
          first_item = last_item = current_item ;
        else
        {
          last_item->next = current_item;
          last_item = current_item;
        }
      } 
    }
  else return (0);

	gtk_init(NULL, NULL);
  GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(GTK_WIDGET(main_window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	GtkWidget *box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(main_window), box);

  dlg_set_css(running_params);
  dlg_window_set_caption(GTK_WINDOW(main_window), running_params);
  dlg_window_move(GTK_WINDOW(main_window), running_params);
  dlg_window_resize(GTK_WINDOW(main_window), running_params);

  for (current_item = first_item ; current_item ; current_item = current_item->next)
  {
    current_item->button = gtk_button_new_with_mnemonic(current_item->label);
    GtkStyleContext *context = gtk_widget_get_style_context(current_item->button);
    gtk_style_context_add_class(context, "menu_button");
    gtk_box_pack_start(GTK_BOX(box), current_item->button , TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(current_item->button), "clicked", G_CALLBACK(st_doAction), current_item);
  }

  // bouton quitter systématique
 	GtkWidget *button_quit = gtk_button_new_with_mnemonic ("_Quitter");
  GtkStyleContext *context = gtk_widget_get_style_context(button_quit);
  gtk_style_context_add_class(context, "menu_button");
  gtk_box_pack_start(GTK_BOX(box), button_quit, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button_quit), "clicked", G_CALLBACK(st_doQuit), main_window);

  gtk_widget_show_all(main_window); // display all
  gtk_main(); // Start infinite loop

  return(1);
}

static void st_doAction(GtkWidget *widget, gpointer user_data)
{
  UNUSED(widget);
  item *it = user_data;
  puts(it->action);
  gtk_main_quit();
}

static void st_doQuit(GtkWidget *widget, gpointer user_data)
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
