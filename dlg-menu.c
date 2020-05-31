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

int dlg_menu_widget(GtkWidget *mainWindow, int first, int last, char**argv)
{
  item *first_item, *current_item, *last_item;
  first_item =  current_item = last_item = 0 ;
  if (first < last)
    {
      while (first < last)
      {
        current_item = (item *)malloc(sizeof(item));
        current_item ->action = argv[first++];
        current_item ->label = argv[first++];
        current_item ->next = 0;

        if (!first_item) first_item = last_item = current_item ;
        else
        {
          last_item->next = current_item;
          last_item = current_item;
        }
      } 
      putchar('\n');
    }
  else return (0);

	GtkWidget *box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(mainWindow), box);

  for (current_item = first_item ; current_item ; current_item = current_item->next)
  {
    current_item->button = gtk_button_new_with_mnemonic(current_item->label);
    gtk_box_pack_start(GTK_BOX(box), current_item->button , TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(current_item->button), "clicked", G_CALLBACK(st_doAction), current_item);
  }

  // bouton quitter systématique
 	GtkWidget *bQuit = gtk_button_new_with_mnemonic ("_Quitter");
  gtk_box_pack_start(GTK_BOX(box), bQuit, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(bQuit), "clicked", G_CALLBACK(st_doQuit), mainWindow);
  return(1);
}

static void st_doAction(GtkWidget *widget, gpointer user_data)
{
  UNUSED(widget);
  item *it = user_data;
  printf("%s\n", it->action);
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
    case GTK_RESPONSE_NONE:
    case GTK_RESPONSE_NO:
        gtk_widget_destroy(w);
        break;
  }
}
