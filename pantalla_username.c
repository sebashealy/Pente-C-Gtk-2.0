#include <gtk-2.0/gtk/gtk.h>
#include <stdio.h>

// Definimos la estructura UserData
typedef struct
{
  GtkWidget *nombre_j1;
  GtkWidget *nombre_j2;
} UserData;

extern void pantalla_juego(GtkWidget *widget, gpointer data);

void guardar_nombres(const char *nombre1, const char *nombre2)
{
  FILE *file = fopen("nombres.txt", "a");
  if (file != NULL)
    {
      fprintf(file, "Jugador 1: %s\n", nombre1);
      fprintf(file, "Jugador 2: %s\n", nombre2);
      fclose(file);
    }
  else
    {
      g_print("Error al abrir el archivo\n");
    }
}

void on_boton_clicked(GtkWidget *boton, gpointer data)
{
  UserData *ud = (UserData *)data;
  const char *nombre_j1 = gtk_entry_get_text(GTK_ENTRY(ud->nombre_j1));
  const char *nombre_j2 = gtk_entry_get_text(GTK_ENTRY(ud->nombre_j2));
  
  guardar_nombres(nombre_j1, nombre_j2);
  pantalla_juego(boton, NULL);
}

void pantalla_username(GtkWidget *widget, gpointer data)
{
  GtkWidget *ventana, *cajaH1, *cajaH2, *caja_vertical, *boton, *label_j1, *label_j2;
  UserData *ud = g_new(UserData, 1);  // Allocate memory for the UserData struct using g_new

  //2. Crear los widgets y fijar sus atributos
  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  caja_vertical = gtk_vbox_new(TRUE, 5);
  cajaH1 = gtk_hbox_new(TRUE, 5);
  cajaH2 = gtk_hbox_new(TRUE, 5);
  boton = gtk_button_new_with_label("JUGAR");
  label_j1 = gtk_label_new("J1:");
  label_j2 = gtk_label_new("J2:");
  ud->nombre_j1 = gtk_entry_new();
  ud->nombre_j2 = gtk_entry_new();

  //2.b. Fijar atributos
  gtk_window_set_title(GTK_WINDOW(ventana), "Ingrese nombre del jugador");

  //3. Registrar las llamdas a las funciones
  g_signal_connect(G_OBJECT(boton), "clicked", G_CALLBACK(on_boton_clicked), ud);

  //4. Definir la jerarquia de las instancias del programa
  gtk_box_pack_start_defaults(GTK_BOX(cajaH1), label_j1);
  gtk_box_pack_start_defaults(GTK_BOX(cajaH1), ud->nombre_j1);
  gtk_box_pack_start_defaults(GTK_BOX(cajaH2), label_j2);
  gtk_box_pack_start_defaults(GTK_BOX(cajaH2), ud->nombre_j2);
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical), cajaH1);
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical), cajaH2);
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical), boton);

  gtk_container_add(GTK_CONTAINER(ventana), caja_vertical);

  //5. Mostrar widgets
  gtk_widget_show_all(ventana);
}
