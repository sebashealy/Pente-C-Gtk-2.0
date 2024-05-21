/******************************************************************************************************************
PENTE

pantalla_ganador_jvj.c
Sebastian Healy - Paolo Corti
Proyecto final -Programacion aplicada
Profesor Tortolero
------------------------------------------------------------------------------------------------------------------
Este modulo muestra una ventana con el nombre del ganador una vez que la partida se acaba.

******************************************************************************************************************/

#include <gtk-2.0/gtk/gtk.h>
#include <stdio.h>
#include <string.h>

void mostrar_ganadores_jvj(GtkWidget *widget, gpointer data);
extern void pantalla_juego(GtkWidget *widget, gpointer data);

void pantalla_ganador_jvj(GtkWidget *widget, char letra)
{

  GtkWidget *ventana, *cajav_global, *cajah_botones, *cajah_tiempo, *label_ganador, *boton_otra, *boton_salir, *label_reloj, *label_tiempo, *abrir_info;
  FILE *fp;//nombres.txt
  FILE *ganadores;
    char linea[100]; // Asumimos que cada línea del archivo tiene menos de 100 caracteres.
     char primerLugar[100]; // Aquí guardaremos el último nombre de Jugador 1 o 2 encontrado.
     char *texto;
     
     fp = fopen("nombres.txt", "r");
     ganadores = fopen("ganadores.txt", "a");
     
  if(letra == 'X')
    {
     while (fgets(linea, sizeof(linea), fp) != NULL) {
        // Chequeamos si la línea comienza con "Jugador 1".
        if (strncmp(linea, "Jugador 1:", 10) == 0) {
       
            // Usamos sscanf para extraer el nombre después de los dos puntos y el espacio.
            sscanf(linea, "Jugador 1: %s", primerLugar);
        }
    } 
    }

       
  if(letra == 'O')
    {
     while (fgets(linea, sizeof(linea), fp) != NULL) {
        // Chequeamos si la línea comienza con "Jugador 2".
        if (strncmp(linea, "Jugador 2:", 10) == 0) {
           
            // Usamos sscanf para extraer el nombre después de los dos puntos y el espacio.
            sscanf(linea, "Jugador 2: %s", primerLugar);
        }
    } 
    }

  fputs(primerLugar, ganadores);
  fprintf(ganadores, "\n");
  
  //2. Crear los widgets y fijar sus atributo
  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  cajav_global = gtk_vbox_new(TRUE, 5);
  cajah_botones = gtk_hbox_new(TRUE, 5);
  cajah_tiempo = gtk_hbox_new(TRUE, 5);
  texto = g_strdup_printf("¡Gana %s!", primerLugar);
  label_ganador = gtk_label_new(texto);
  label_reloj = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_reloj), "<span font='Symbola, FontAwesome'>⌛</span>");
  label_tiempo = gtk_label_new("00:00");
  //gtk_label_set_text(GTK_LABEL(label_tiempo), time_str); 
  boton_otra = gtk_button_new_with_label("Jugar de nuevo");
  boton_salir = gtk_button_new_with_label("Salir");
  abrir_info = gtk_button_new_with_label("Leaderboard");

   GdkColor color_titulo, color_nombres, color_botones;

   // Color para los botones
  gdk_color_parse("#FFA500", &color_botones);
  gtk_widget_modify_bg(boton_salir, GTK_STATE_NORMAL, &color_botones);
  gtk_widget_modify_bg(boton_otra, GTK_STATE_NORMAL, &color_botones);
  gtk_widget_modify_bg(abrir_info, GTK_STATE_NORMAL, &color_botones);

  //2.b. Fijar atributos
  gtk_window_set_title(GTK_WINDOW(ventana), "Partida acabada");

   //3. Registrar las llamadas a las funciones
  g_signal_connect(G_OBJECT(boton_salir), "clicked", G_CALLBACK( gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(boton_otra), "clicked", G_CALLBACK(pantalla_juego), NULL);
  g_signal_connect(G_OBJECT(abrir_info), "clicked", G_CALLBACK(mostrar_ganadores_jvj), ventana);

  //4. Definir la jerarquia de las instancias del programa
  gtk_container_set_border_width(GTK_CONTAINER(ventana), 10);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_tiempo), label_reloj);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_tiempo), label_tiempo);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_botones), boton_otra);
   gtk_box_pack_start_defaults(GTK_BOX(cajah_botones), abrir_info);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_botones), boton_salir);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_global), label_ganador);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_global), cajah_tiempo);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_global), cajah_botones);
  gtk_container_add(GTK_CONTAINER(ventana), cajav_global);

  
 //5. Mostrar widgets
  gtk_widget_show_all(ventana);

  fclose(fp);
  fclose(ganadores);
}

void mostrar_ganadores_jvj(GtkWidget *widget, gpointer data)
{
  //1. Declaracion de variables
  GtkWidget *dialog, *label, *pestana;
  GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
  char username[1024];
  FILE *file;
  size_t tamano;

  //Apertura del archivo en modo de lectura
  file = fopen("nombres.txt", "r");
  if (file == NULL)
    {
      perror("Error al abrir el archivo");
      return;
    }

  //2. Crear los widgets y fijar sus atributo
  dialog = gtk_dialog_new_with_buttons("Ganadores", GTK_WINDOW(data), flags,"_Cerrar", GTK_RESPONSE_CLOSE, NULL);
  pestana = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
  label = gtk_label_new(NULL);
  
  tamano = fread(username, sizeof(char), sizeof(username) - 1, file);
  username[tamano] = '\0';
  
  gtk_label_set_text(GTK_LABEL(label), username);
  
  //3. Registrar llamado a funciones
  g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);

  //4. Definir la jerarquia de las instancias del programa
  gtk_container_add(GTK_CONTAINER(pestana), label);
  
  //5. Mostrar widgets
  gtk_widget_show_all(dialog);
  fclose(file);
}


