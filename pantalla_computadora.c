#include <gtk-2.0/gtk/gtk.h>

extern void juego(GtkWidget *widget, gpointer data);

void pantalla_computadora(GtkWidget *widget, gpointer data)
{
 //Se declara una variable por cada widget. Todas las declaraciones se deben de declarar como apuntadores.
  GtkWidget *ventana, *cajaH1, *caja_vertical, *boton, *nombre_j1, *label_j1;

  //2. Crear los widgets y fijar sus atributos
  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  caja_vertical = gtk_vbox_new(TRUE, 5);
  cajaH1 = gtk_hbox_new(TRUE, 5);
  boton =  gtk_button_new_with_label("JUGAR");
  label_j1 = gtk_label_new("Nombre del jugador:");
  nombre_j1 = gtk_entry_new();

   //2.b. Fijar atributos
  gtk_window_set_title(GTK_WINDOW(ventana), "Ingrese nombre del jugador");

  //3. Registrar las llamdas a las funciones
  g_signal_connect(G_OBJECT(boton), "clicked", G_CALLBACK(juego), NULL);

  //4. Definir la jerarquia de las instancias del programa
  gtk_box_pack_start_defaults(GTK_BOX(cajaH1), label_j1);
  gtk_box_pack_start_defaults(GTK_BOX(cajaH1), nombre_j1);
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical), cajaH1);
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical), boton);

  gtk_container_add(GTK_CONTAINER(ventana), caja_vertical);

   //5. Mostrar widgets
  gtk_widget_show_all(ventana);
  
  //6. Procesar senales y eventos
  gtk_main();
}
