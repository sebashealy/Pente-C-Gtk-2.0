#include <gtk-2.0/gtk/gtk.h>

extern void juego(void);
extern void pantalla_principal(void);

gint main (gint argc, gchar *argv[])
{
 
  //1. Inicializar el ambiente
  gtk_init(&argc, &argv);

   pantalla_principal();

   //juego();
  
   //6. Procesar las señales y los eventos
  gtk_main();
  
  return 0;
}