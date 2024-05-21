******************************************************************************************************************
PENTE

pantalla_principal.c
Sebastian Healy - Paolo Corti
Proyecto final -Programacion aplicada
Profesor Tortolero
------------------------------------------------------------------------------------------------------------------
Este modulo muestra la pantalla de inicio del juego. Esta portada incluye:
- Nombre del juego
- Nombre de los desarrolladores
- Boton de reglas
--> Ventana con las reglas del juego
- Boton de creditos
--> Creditos e informacion adicional del codigo
-Boton jugar
--> Abre la pestania del modo de juego

******************************************************************************************************************/

#include <gtk-2.0/gtk/gtk.h>

//Declararcion de funciones
gboolean cerrar_ventana(GtkWidget *widget, GdkEvent *event, gpointer data);
void salir (GtkWidget *widget, gpointer data);
void creditos(GtkWidget *boton_creditos, gpointer data);
void reglas(GtkWidget *boton_reglas, gpointer data);
void jugar(GtkWidget *boton_reglas, gpointer data);
//extern void pantalla_juego(GtkWidget *widget, gpointer data);
extern void pantalla_username(GtkWidget *widget, gpointer data);
extern void pantalla_computadora(GtkWidget *widget, gpointer data);

void pantalla_principal(void)
{
 //Se declara una variable por cada widget. Todas las declaraciones se deben de declarar como apuntadores.
  GtkWidget *ventana, *caja_vertical, *caja_horizontal, *texto_titulo, *texto_nombres, *boton_creditos, *boton_jugar, *boton_reglas, *caja_vertical_texto;

   //2. Crear los widgets y fijar sus atributos
  ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  caja_vertical = gtk_vbox_new(TRUE, 5);
  caja_vertical_texto = gtk_vbox_new(TRUE, 5);
  caja_horizontal = gtk_hbox_new(TRUE, 5);
  texto_titulo = gtk_label_new("Pente - El juego"); //Titulo
  texto_nombres = gtk_label_new("Por Sebastian Healy y Paolo Corti"); //Nombres del equipo
  boton_creditos =  gtk_button_new_with_label("Creditos");
  boton_jugar =  gtk_button_new_with_label("JUGAR");
  boton_reglas =  gtk_button_new_with_label("Reglas");

  //Aumentar de tamano el titulo
  PangoFontDescription *font_desc = pango_font_description_new();
  pango_font_description_set_size(font_desc, 20 * PANGO_SCALE);
  gtk_widget_modify_font(texto_titulo, font_desc);
  pango_font_description_free(font_desc);

  // Agregar colores
  GdkColor color_titulo, color_nombres, color_botones;

  // Color para el título
  gdk_color_parse("#0000FF", &color_titulo);
  gtk_widget_modify_fg(texto_titulo, GTK_STATE_NORMAL, &color_titulo);

  // Color para los nombres
  gdk_color_parse("#008000", &color_nombres);
  gtk_widget_modify_fg(texto_nombres, GTK_STATE_NORMAL, &color_nombres);

  // Color para los botones
  gdk_color_parse("#FFA500", &color_botones);
  gtk_widget_modify_bg(boton_creditos, GTK_STATE_NORMAL, &color_botones);
  gtk_widget_modify_bg(boton_jugar, GTK_STATE_NORMAL, &color_botones);
  gtk_widget_modify_bg(boton_reglas, GTK_STATE_NORMAL, &color_botones);

  //3. Registrar las llamadas a las funciones
  //Cerrar ventana
  g_signal_connect(G_OBJECT(ventana), "delete_event", G_CALLBACK(cerrar_ventana), NULL);
  g_signal_connect(G_OBJECT(ventana), "destroy", G_CALLBACK(salir), NULL);
  //Creditos
  g_signal_connect(G_OBJECT(boton_creditos), "clicked", G_CALLBACK(creditos), NULL );
  //Reglas
  g_signal_connect(G_OBJECT(boton_reglas), "clicked", G_CALLBACK(reglas), NULL );
  //Jugar
  g_signal_connect(G_OBJECT(boton_jugar), "clicked", G_CALLBACK(jugar), NULL );
  
  
  //4. Definir la jerarquia de las instancias del programa
  //Botones funcionales
  gtk_box_pack_start_defaults(GTK_BOX(caja_horizontal), boton_creditos);
  gtk_box_pack_start_defaults(GTK_BOX(caja_horizontal), boton_jugar);
  gtk_box_pack_start_defaults(GTK_BOX(caja_horizontal), boton_reglas);

  //Textos
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical_texto), texto_titulo);
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical_texto), texto_nombres);
  
  //Orden vertical en pantalla
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical), caja_vertical_texto);
  gtk_box_pack_start_defaults(GTK_BOX(caja_vertical), caja_horizontal);

  //Ventana
  gtk_container_add(GTK_CONTAINER(ventana), caja_vertical);

  //5. Mostrar los widgets
  gtk_widget_show_all(ventana);
}

//Funcion para cerrar la ventana
gboolean cerrar_ventana(GtkWidget *widget, GdkEvent *event, gpointer data)
{
  return FALSE;
}

//Funcion para terminar la ejecucion del programa
void salir (GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}

//Creditos del juego
void creditos(GtkWidget *boton_creditos, gpointer data) 
{
    // Crear una nueva ventana para los créditos
    GtkWidget *ventana_creditos = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana_creditos), "Créditos");
    gtk_container_set_border_width(GTK_CONTAINER(ventana_creditos), 10);
    
    // Crear un label con el contenido de los créditos
    GtkWidget *label_creditos = gtk_label_new("Desarrollado por:\nSebastian Healy y Paolo Corti\n\nCodigo escrito en C\n\nMateria:\nProgramacion aplicada\n\nDocente:\nAndres Tortolero\n\nCurso:\nPrimavera 2024\n");
    
    // Añadir el label a la ventana
    gtk_container_add(GTK_CONTAINER(ventana_creditos), label_creditos);
    
    // Mostrar todo
    gtk_widget_show_all(ventana_creditos);
}

//Reglas del juego
void reglas(GtkWidget *boton_reglas, gpointer data)
{
    // Crear una nueva ventana para los créditos
    GtkWidget *ventana_reglas = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana_reglas), "Reglas");
    gtk_container_set_border_width(GTK_CONTAINER(ventana_reglas), 10);
    
    // Crear un label con el contenido de los créditos
    GtkWidget *label_reglas = gtk_label_new("**Reglas del Juego de Pente**\n\n**Objetivo:**\nEl objetivo del juego es ser el primero en colocar cinco piedras propias consecutivas en línea recta, capturar 12 piedras del oponente o hacer 5 lineas rectas de cuatro fichas.\n\n**Inicio del Juego:**\n1. El juego se juega en un tablero de tamaño 20x20 (aunque puede variar).\n2. Los jugadores eligen un color de piedras.\n\n**Movimientos:**\n1. Los jugadores toman turnos para colocar una piedra de su color en el tablero en cualquier cuadrado vacío.\n2. Después del primer movimiento, los jugadores pueden capturar piedras del oponente.\n\n**Captura:**\n1. Un jugador puede capturar piedras del oponente si coloca dos de sus piedras adyacentes horizontalmente, verticalmente o diagonalmente a dos piedras que estan juntas  del oponente. (es decir encierra dos piedras del oponente)\n2. Las piedras del oponente capturadas se eliminan del tablero..\n\n**Ganar:**\n1. El juego termina cuando un jugador logra colocar cinco piedras consecutivas en línea horizontal, vertical o diagonalmente.\n2. También se puede ganar capturando doce piedras del oponente.\n3.Haciendo cinvo lineas rectas de 4 piedras\n4. Si no hay más movimientos posibles, el juego termina en un empate.\n\n¡Que gane el mejor estratega!\n");
    
    // Añadir el label a la ventana
    gtk_container_add(GTK_CONTAINER(ventana_reglas), label_reglas);
    
    // Mostrar todo
    gtk_widget_show_all(ventana_reglas);
}

//Iniciar el juego
void jugar(GtkWidget *boton_jugar, gpointer data)
{
    // Crear una nueva ventana para los creditos
    GtkWidget *ventana_jugar = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ventana_jugar), "jugar");
    gtk_container_set_border_width(GTK_CONTAINER(ventana_jugar), 10);

    GtkWidget *caja_horizontal = gtk_hbox_new(TRUE, 5);
    // Crear los botones
    GtkWidget *boton_jugador = gtk_button_new_with_label("J v J");
    GtkWidget *boton_maquina = gtk_button_new_with_label("J v M");

    GdkColor color_titulo, color_nombres, color_botones;

    // Color para los botones
    gdk_color_parse("#FFA500", &color_botones);
    gtk_widget_modify_bg(boton_jugador, GTK_STATE_NORMAL, &color_botones);
    gtk_widget_modify_bg(boton_maquina, GTK_STATE_NORMAL, &color_botones);
  
    // Conectar señales si es necesario
    g_signal_connect(G_OBJECT(boton_jugador), "clicked", G_CALLBACK(pantalla_username), NULL); //Funcion para recibir nombres - JvJ
    g_signal_connect(G_OBJECT(boton_maquina), "clicked", G_CALLBACK(pantalla_computadora), NULL); //Funcion para recibir el nombre 
    gtk_box_pack_start(GTK_BOX(caja_horizontal), boton_jugador, TRUE, TRUE, 0); 
    gtk_box_pack_start(GTK_BOX(caja_horizontal), boton_maquina, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(ventana_jugar), caja_horizontal);

    
    // Mostrar todo
    gtk_widget_show_all(ventana_jugar);

    
}
 
