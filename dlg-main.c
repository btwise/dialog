#include <stdio.h>
#include <getopt.h>
#include <dlg.h>

static GtkWidget *st_gui_init(char *caption, char *css_file);
static void st_usage(char *my_name);
static void st_version(char *my_name);

int main(int argc, char **argv)
{
  int c;
  static int verbose_flag; // Flag set by ‘--verbose’
  static int whish_widget; // which widget display ?
  static char *caption; // window name
  static char *css_filename; // CSS file name

  while(1)
  {
    static struct option long_options[] =
    {
      // These options set a flag
      {"verbose", no_argument,       &verbose_flag, 1},
      {"brief",   no_argument,       &verbose_flag, 0},
      {"menu",    no_argument,       &whish_widget, 'm'},
      {"yesno",   no_argument,       &whish_widget, 'y'},
      // These options don’t set a flag. We distinguish them by their indices
      {"help",    no_argument,       0, 'h'},
      {"version", no_argument,       0, 'v'},
      {"title",   required_argument, 0, 't'},
      {"css",     required_argument, 0, 'c'},
      {0, 0, 0, 0}
    };

    // getopt_long stores the option index here
    int option_index = 0;

    c = getopt_long(argc, argv, "myt:c:hv", long_options, &option_index);

    if (c == -1) // Detect the end of the options
      break;

    switch (c)
      {
      case 0:
        // If this option set a flag, do nothing else now
        if (long_options[option_index].flag != 0)
          break;
        printf("option %s", long_options[option_index].name);
        if (optarg)
          printf(" with arg %s", optarg);
        printf("\n");
        break;

      case 't':
        caption = optarg;
        break;

      case 'c':
        css_filename = optarg;
        break;

      case 'h':
        st_usage(argv[0]);
        exit(0);
        break;

      case 'v':
        st_version(argv[0]);
        exit(0);
        break;

      case '?': // getopt_long already printed an error message
        break;

      default:
        abort();
      }
  }
  /* Instead of reporting ‘--verbose’ and ‘--brief’ as they are encountered,
     we report the final status resulting from them.
  if (verbose_flag)
    puts ("verbose flag is set");
  */

  GtkWidget *main_window = st_gui_init(caption, css_filename);
  switch (whish_widget)
    {
    case 'm' :
      if (!dlg_menu_widget(main_window, optind, argc, argv))
        exit(1);
      break;
    case 'y' :
      break;
    default:
      abort();
    }

	// affichage
	gtk_widget_show_all(main_window);
  // lancement de la boucle infinie
	gtk_main();

  exit (0);
}

GtkWidget *st_gui_init(char *caption, char *css_filename)
{
  UNUSED(css_filename); // provisional

	gtk_init(NULL, NULL);
  GtkWidget *mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  if (caption)
    gtk_window_set_title(GTK_WINDOW(mainWindow), caption);
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), -1, -1);
	gtk_window_move(GTK_WINDOW(mainWindow), 1150, 0);
  return mainWindow;
}

void st_usage(char *my_name)
{
  printf("%s :\n", my_name); 
  puts ("\t--verbose");
  puts ("\t--brief");
  puts ("\t--menu");
  puts ("\t--yesno");
  puts ("\t--theme=<css-file>");
  puts ("\t--help");
  puts ("\t--version");
}

void st_version(char *my_name)
{
  printf("%s : version 0\n", my_name); 
}

/* Print any remaining command line arguments (not options)
static void st_display_args(int first, int last, char**argv);
void st_display_args(int first, int last, char**argv)
{
  if (first < last)
    {
      printf(" ARGV-elements: ");
      while (first < last)
        printf("%s ", argv[first++]);
      putchar('\n');
    }
}
. */
