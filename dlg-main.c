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
      {"menu",     no_argument,       &wish_widget, 'm'},
      {"yesno",    no_argument,       &wish_widget, 'y'},
      {"help",     no_argument,       0, 'h'},
      {"version",  no_argument,       0, 'v'},
      {"caption",  required_argument, 0, 'c'},
      {"position", required_argument, 0, 'p'},
      {"size",     required_argument, 0, 's'},
      {"theme",    required_argument, 0, 'T'},
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

      case 'c':
        running_params->caption = optarg;
        break;

      case 'p':
        if (!st_decode_coordinates(optarg, &running_params->posx, &running_params->posy))
        {
          st_usage(argv[0]);
          run = FALSE;
        }
        break;

      case 's':
        if (!st_decode_coordinates(optarg, &running_params->width, &running_params->height))
        {
          st_usage(argv[0]);
          run = FALSE;
        }
        break;

      case 'T':
        running_params->css_filename = optarg;
        break;

      case 'h':
        st_usage(argv[0]);
        run = FALSE;
        break;

      case 'v':
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
      case 'm' :
        run = dlg_menu_widget(running_params);
        break;
      case 'y' :
        run = dlg_yesno_widget(running_params);
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
  puts ("\t--caption=<caption-string>");
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
