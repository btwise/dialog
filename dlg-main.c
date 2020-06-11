#include <stdio.h>
#include <getopt.h>
#include <dlg.h>

static void st_usage(char *my_name);
static void st_version(char *my_name);
static int st_decode_coordinates(char* s, int *x, int *y);
dlg_params *dlg_params_new(void);

int main(int argc, char **argv)
{
  int c;
  int run = TRUE;
  static int wish_widget = { 0 }; // wich widget to chose ?
  dlg_params *running_params = dlg_params_new();

  while(run)
  {
    static struct option long_options[] =
    {
      {"menu",      no_argument,       &wish_widget, DLG_MENU},
      {"yesno",     no_argument,       &wish_widget, DLG_YESNO},
      {"list",      no_argument,       &wish_widget, DLG_LIST},
      {"help",      no_argument,       0, DLG_HELP},
      {"version",   no_argument,       0, DLG_VERSION},
      {"caption",   required_argument, 0, DLG_CAPTION},
      {"title",     required_argument, 0, DLG_TITLE},
      {"position",  required_argument, 0, DLG_POSITION},
      {"size",      required_argument, 0, DLG_SIZE},
      {"theme",     required_argument, 0, DLG_THEME},
      {0, 0, 0, 0}
    };

    // getopt_long stores the option index here
    int option_index = 0;

    c = getopt_long(argc, argv, "myc:T:hv", long_options, &option_index);

    if (c == -1) // Detect the end of the options
      break;

    switch (c)
      {
      case 0: // option which set a flag, do nothing else now
        break;

      case DLG_CAPTION:
        running_params->caption = optarg;
        break;

      case DLG_TITLE:
        running_params->title = optarg;
        break;

      case DLG_POSITION:
        if (!st_decode_coordinates(optarg, &running_params->posx, &running_params->posy))
        {
          st_usage(argv[0]);
          run = FALSE;
        }
        break;

      case DLG_SIZE:
        if (!st_decode_coordinates(optarg, &running_params->width, &running_params->height))
        {
          st_usage(argv[0]);
          run = FALSE;
        }
        break;

      case DLG_THEME:
        running_params->css_filename = optarg;
        break;

      case DLG_HELP:
        st_usage(argv[0]);
        run = FALSE;
        break;

      case DLG_VERSION:
        st_version(argv[0]);
        run = FALSE;
        break;

      case '?': // getopt_long already printed an error message
        run = FALSE;
        break;

      default:
        abort();
      }
  }

  running_params->first = optind;
  running_params->last  = argc;
  running_params->argv  = argv;

  if (run & !wish_widget)
  {
    puts("widget required");
    run = FALSE;
  }

  if (run)
  {
    switch (wish_widget)
      {
      case DLG_MENU :
        run = dlg_menu_widget(running_params);
        break;
      case DLG_YESNO :
        run = dlg_yesno_widget(running_params);
        break;
      case DLG_LIST :
        run = dlg_list_widget(running_params);
        break;
      default:
        abort();
        break;
      }
  }
 
 exit(run ? 0 : 1);
}

void st_usage(char *my_name)
{
  printf("%s :\n", my_name); 
  puts ("\t--menu");
  puts ("\t--yesno");
  puts ("\t--list");
  puts ("\t--caption=<caption-string>");
  puts ("\t--title=<title-string>");
  puts ("\t--theme=<css-file>");
  puts ("\t--position=<x-value>x<y-value>");
  puts ("\t--size=<x-value>x<y-value>");
  puts ("\t--help");
  puts ("\t--version");
}

void st_version(char *my_name)
{
  printf("%s : version 0\n", my_name); 
}

dlg_params *dlg_params_new(void)
{
  dlg_params *p = (dlg_params *)malloc(sizeof(dlg_params));
  p->caption = 0;
  p->css_filename = 0;
  p->posx = -1;
  p->posy = -1;
  p->width = -1;
  p->height = -1;
  p->first = 0;
  p->last = 0;
  p->argv = 0;
  return (p);
}

static int st_decode_coordinates(char *s, int *x, int *y)
{
  gchar **v = g_strsplit_set(s, "xX", 2);
  if (v[0]) *x = atoi(v[0]);
  if (v[1]) *y = atoi(v[1]);
  g_strfreev(v);
  return((*x == -1 || *y == -1) ? FALSE : TRUE) ;
}
