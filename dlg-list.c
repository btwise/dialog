#include <dlg.h>

//static void tree_selection_changed_cb(GtkTreeSelection *selection, gpointer data);
static void st_ok(GtkTreeSelection *selection, gpointer user_data);
static void st_cancel(GtkWidget *widget, gpointer user_data);

enum
{
  LIST_KEY,
  LIST_LABEL,
  N_COLUMNS
};

int dlg_list_widget(dlg_params *running_params)
{
  const int nbitems = (running_params->last - running_params->first) / 2;
  GtkListStore *list_store = { 0 };
  GtkTreeIter iter;
  if (nbitems)
    {
      list_store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
      for (int i = 0 ; i < nbitems ; i++)
      {
        char *key = running_params->argv[running_params->first++];
        char *label = running_params->argv[running_params->first++];
        gtk_list_store_append(list_store, &iter);
        gtk_list_store_set (list_store, &iter, LIST_KEY, key, LIST_LABEL, label, -1);
      } 
    }
  else return (0);

	gtk_init(NULL, NULL);
  GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(GTK_WIDGET(main_window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add(GTK_CONTAINER(main_window), main_box);
  gtk_container_set_border_width(GTK_CONTAINER(main_box), 10);

  if (running_params->title)
  {
    GtkWidget *title = gtk_label_new(running_params->title);
    gtk_box_pack_start(GTK_BOX(main_box), title, TRUE, TRUE, 0);
  }

  GtkWidget *tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL (list_store));
  gtk_box_pack_start(GTK_BOX(main_box), tree, TRUE, TRUE, 0);
  gtk_widget_set_size_request(tree, 250, -1);

  GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
  GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes("Titre colonne", renderer, "text", LIST_LABEL, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW (tree), column);
  GtkTreeSelection *select= gtk_tree_view_get_selection(GTK_TREE_VIEW(tree));
  gtk_tree_selection_set_mode(select, GTK_SELECTION_SINGLE);
  //  g_signal_connect(G_OBJECT(select), "selected", G_CALLBACK(tree_selection_changed_cb), NULL);

  dlg_set_css(running_params);
  dlg_window_set_caption(GTK_WINDOW(main_window), running_params);
  dlg_window_move(GTK_WINDOW(main_window), running_params);
  dlg_window_resize(GTK_WINDOW(main_window), running_params);


	GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_spacing(GTK_BOX(button_box), 10);
  gtk_box_pack_start(GTK_BOX(main_box), button_box, TRUE, TRUE, 0);

 	GtkWidget *button_ok = gtk_button_new_with_mnemonic ("_OK");
  gtk_widget_set_size_request(button_ok, 120, -1);
  gtk_box_pack_start(GTK_BOX(button_box), button_ok, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button_ok), "clicked", G_CALLBACK(st_ok), select);

 	GtkWidget *button_cancel = gtk_button_new_with_mnemonic ("_Cancel");
  gtk_widget_set_size_request(button_cancel, 120, -1);
  gtk_box_pack_start(GTK_BOX(button_box), button_cancel, TRUE, TRUE, 0);
  g_signal_connect(G_OBJECT(button_cancel), "clicked", G_CALLBACK(st_cancel), main_window);

  gtk_widget_show_all(main_window); // display all
  gtk_main(); // Start infinite loop

  return(1);
}

/*
static void tree_selection_changed_cb(GtkTreeSelection *selection, gpointer data)
{
  UNUSED(data);
  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *key;
  if (gtk_tree_selection_get_selected(selection, &model, &iter))
  {
    gtk_tree_model_get(model, &iter, LIST_KEY, &key, -1);
    g_print ("key=%s\n", key);
    g_free (key);
  }
}
*/

static void st_ok(GtkTreeSelection *selection, gpointer user_data)
{
  UNUSED(selection);
  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *key;
  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(user_data), &model, &iter))
  {
    gtk_tree_model_get(model, &iter, LIST_KEY, &key, -1);
    puts(key);
    g_free(key);
  gtk_main_quit();
  }
}

static void st_cancel(GtkWidget *widget, gpointer user_data)
{
  UNUSED(widget);
  gtk_main_quit();
  gtk_widget_destroy(user_data);
}
