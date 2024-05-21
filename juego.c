/******************************************************************************************************************
PENTE

juego.c
Sebastian Healy - Paolo Corti
Proyecto final -Programacion aplicada
Profesor Tortolero
------------------------------------------------------------------------------------------------------------------
Este modulo permite la modalidad de juego jugador v. computadora. Estructuralmente es lo mismo que la funcion de pantalla_juego.c en donde se juega JvJ. En este modulo, se adapta un algoritmo que permite jugar contra el CPU. 

******************************************************************************************************************/

#include <gtk-2.0/gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

gboolean cerrar_fenetre2(GtkWidget *widget, GdkEvent *event, gpointer data);
void informacion2(GtkWidget *boton_creditos, gpointer data);
void instrucciones2(GtkWidget *boton_reglas, gpointer data);
void color_boton2(GtkWidget *widget, gchar player);
extern void pantalla_ganador(GtkWidget *widget, char letra);
void button_clicked2(GtkWidget *widget, gpointer data);
void color_boton2(GtkWidget *widget, gchar player);
int verifica_5_2(gchar matriz[20][20], char check);
int verificador_4_2(gchar matriz[20][20], char check); //funcion que cuenta el numero de lineas rectas echas y condicionamos para verificar si es igual a 4
int verificar_encerradas_hi2(gchar matriz[20][20], gint row, gint column);
int verificar_encerradas_hd2(gchar matriz[20][20], gint row, gint column);
int verificar_encerradas_v_arriba2(gchar matriz[20][20], gint row, gint column);
int verificar_encerradas_v_abajo2(gchar matriz[20][20], gint row, gint column);
int verificar_encerradas_diagonal_arrd2(gchar matriz[20][20], gint row, gint column);
int verificar_encerradas_diagonal_arr_iz2(gchar matriz[20][20], gint row, gint column);
int verificar_encerradas_diagonal_abiz2(gchar matriz[20][20], gint row, gint column);
int verificar_encerradas_diagonal_abd2(gchar matriz[20][20], gint row, gint column);
static gboolean update_time_label2(gpointer data);
void imprime2(gchar matriz[20][20]);
void hacer_movimiento_cpu(gchar matriz[20][20], GtkWidget *widget);
void actualizar_ui_despues_de_cpu(int row, int col, GtkWidget *widget);
GtkWidget* buscar_boton_por_posicion(int i, int j, GtkWidget *widget);

void juego(GtkWidget *widget, gpointer data)
{
  //declaramos la matriz que se va a utilizar para las mecanicas del juego
  gchar (*matriz)[20] = malloc(20 * 20 * sizeof(gchar));
 
  //Se declara una variable por cada widget. Todas las declaraciones se deben de declarar como apuntadores.
  GtkWidget *ventana_juego, *cajav_global, *cajav_tablero, *cajav_informacion, *cajah_principal, *cajah_nombres, *cajah_fichas, *cajah_undo, *cajah_tiempo, *label_titulo, *linea, *label_ficha1, *label_ficha2, *label_comidas1, *label_comidas2, *boton_undo, *boton_redo, *label, *label_reloj, *label_nombre1, *label_nombre2, *label_ficha_color1, *label_ficha_color2, *tablero, *botones, *linea2, *linea3, *separador;

  GtkWidget *menubar, *menu_archivo, *menu_item_jugar, *menu_item_archivo, *menu_item_guardar, *menu_item_deshacer, *menu_item_rehacer, *menu_item_recuperar, *menu_item_terminar, *menu_ayuda, *menu_item_ayuda, *menu_item_instrucciones, *menu_item_creditos, *menu_item_jvj, *menu_item_cpu, *menu_jugar;

  gint row, column, x, y;
  gint *contador_X = g_new(gint, 1);
  gint *contador_O = g_new(gint, 1);
  char lineas[100];
  char t1[50];
  char t2[50];
  FILE *fp;//nombres.txt
  char *texto1, *texto2;
  *contador_X = 0;
  *contador_O = 0;
  fp = fopen("nombres.txt", "r");
  
  //Llenamos la matriz inicial
  for(x = 0; x < 20; x++)
    {
      for(y = 0; y < 20; y++)
	{
	  matriz[x][y] = '.';
	}
    }
  
  while (fgets(lineas, sizeof(lineas), fp) != NULL)
    {
      // Copiar la última línea a la penúltima línea y la línea actual a la última.
      strcpy(t1, t2);
      // Guardar la nueva línea en la última línea.
      strcpy(t2, lineas);
    }//bucle que utilizamos para buscar los nombres indicados en nuestro archivo y lo ensenamos en pantalla
  
  
  //2. Crear los widgets y fijar sus atributo
  ventana_juego = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  tablero = gtk_table_new(20, 20, TRUE);
  cajav_global = gtk_vbox_new(FALSE, 5);
  cajav_tablero = gtk_vbox_new(TRUE, 5);
  cajav_informacion = gtk_vbox_new(TRUE, 5);
  cajah_principal = gtk_hbox_new(TRUE, 5);
  cajah_nombres = gtk_hbox_new(TRUE, 5);
  cajah_fichas = gtk_hbox_new(TRUE, 5);
  cajah_undo = gtk_hbox_new(TRUE, 5);
  cajah_tiempo = gtk_hbox_new(TRUE, 5);
  label_titulo = gtk_label_new("Pente");
  linea  =  gtk_hseparator_new();
  label_ficha1 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_ficha1), "<span foreground='black'>&#9899;</span>");
  label_ficha2 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_ficha2), "<span foreground='grey'>&#9898;</span>");
  label_comidas1 = gtk_label_new("x 0");
  label_comidas2 = gtk_label_new("x 0");
  boton_undo = gtk_button_new_with_label("⬅️");
  boton_redo = gtk_button_new_with_label("➡️");
  label = gtk_label_new("00:00");
  label_reloj = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_reloj), "<span font='Symbola, FontAwesome'>⌛</span>");
  texto1 =  g_strdup_printf("%s:", t1);
  texto2 =  g_strdup_printf("%s:", t2);
  label_nombre1 = gtk_label_new(texto1);
  label_nombre2 = gtk_label_new(texto2);
  label_ficha_color1 = gtk_label_new(NULL);
  label_ficha_color2 = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label_ficha_color1), "<span foreground='black'>&#9899;</span>");
  gtk_label_set_markup(GTK_LABEL(label_ficha_color2), "<span foreground='grey'>&#9898;</span>");
  linea2  =  gtk_hseparator_new();
  linea3 =  gtk_hseparator_new();
  separador =  gtk_vseparator_new();

  g_object_set_data(G_OBJECT(ventana_juego), "contador_X", contador_X);
  g_object_set_data(G_OBJECT(ventana_juego), "contador_O", contador_O);
 
  //crear tablero de botones
  for(row = 0; row < 20; row++)
    {
      for(column = 0; column < 20; column++)
	{
	  botones = gtk_button_new();
	  gtk_table_attach_defaults(GTK_TABLE(tablero), botones, column, column+1, row, row+1);
	  g_object_set_data(G_OBJECT(botones), "row", GINT_TO_POINTER(row));
	  g_object_set_data(G_OBJECT(botones), "column", GINT_TO_POINTER(column));
	  g_signal_connect(botones, "clicked", G_CALLBACK(button_clicked2), matriz);
	}
    }

  menubar = gtk_menu_bar_new();
  menu_archivo = gtk_menu_new();
  menu_item_archivo = gtk_menu_item_new_with_label("Menu");
  menu_ayuda = gtk_menu_new();
  menu_item_ayuda = gtk_menu_item_new_with_label("Ayuda");
  menu_item_instrucciones = gtk_menu_item_new_with_label("Instrucciones");
  menu_item_creditos = gtk_menu_item_new_with_label("Acerca de");
  menu_item_jugar = gtk_menu_item_new_with_label("Jugar");
  menu_jugar = gtk_menu_new();
  menu_item_jvj = gtk_menu_item_new_with_label("J v J");
  menu_item_cpu = gtk_menu_item_new_with_label("J v CPU");
  menu_item_guardar = gtk_menu_item_new_with_label("Guardar");
  menu_item_deshacer = gtk_menu_item_new_with_label("Deshacer");
  menu_item_rehacer = gtk_menu_item_new_with_label("Rehacer");
  menu_item_recuperar = gtk_menu_item_new_with_label("Recuperar");
  menu_item_terminar = gtk_menu_item_new_with_label("Terminar");

  //2.b. Fijar atributos
  gtk_window_set_title(GTK_WINDOW(ventana_juego), "partida");

  //3. Registrar las llamadas a las funciones
  g_signal_connect(G_OBJECT(menu_item_terminar), "activate", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(ventana_juego), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(ventana_juego), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(menu_item_instrucciones), "activate", G_CALLBACK(instrucciones2), NULL );
  g_signal_connect(G_OBJECT(menu_item_creditos), "activate", G_CALLBACK(informacion2), NULL );
  g_signal_connect(G_OBJECT(menu_item_jvj), "activate", G_CALLBACK(cerrar_fenetre2), NULL);
  g_signal_connect(G_OBJECT(menu_item_jvj), "activate", G_CALLBACK(juego), NULL);
  g_signal_connect(G_OBJECT(menu_item_cpu), "activate", G_CALLBACK(juego), NULL);
  
 
  //4. Definir la jerarquia de las instancias del programa
  gtk_container_set_border_width(GTK_CONTAINER(ventana_juego), 10);

  //Menu
  //Menu menu
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_jugar), menu_item_jvj);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_jugar), menu_item_cpu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menu_item_jugar);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_jugar), menu_jugar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menu_item_guardar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menu_item_deshacer);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menu_item_rehacer);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menu_item_recuperar);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menu_item_terminar);
  //Menu ayuda
  gtk_menu_shell_append(GTK_MENU_SHELL(menu_ayuda), menu_item_instrucciones);
   gtk_menu_shell_append(GTK_MENU_SHELL(menu_ayuda), menu_item_creditos);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_archivo), menu_archivo);
  gtk_menu_bar_append(GTK_MENU_BAR(menubar), menu_item_archivo);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_ayuda), menu_ayuda);
  gtk_menu_bar_append(GTK_MENU_BAR(menubar), menu_item_ayuda);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_global), menubar);
 
  //Tablero
  gtk_box_pack_start(GTK_BOX(cajav_tablero), tablero, TRUE, TRUE, 0);
 
  //Info
  //Fichas
  gtk_box_pack_start_defaults(GTK_BOX(cajah_fichas), label_ficha1);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_fichas), label_comidas1);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_fichas), label_ficha2);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_fichas), label_comidas2);
  //Undo
  gtk_box_pack_start_defaults(GTK_BOX(cajah_undo), boton_undo);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_undo), separador);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_undo), boton_redo);
  //Tiempo
  gtk_box_pack_start_defaults(GTK_BOX(cajah_tiempo), label_reloj);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_tiempo), label);
  //Empaque
  gtk_box_pack_start_defaults(GTK_BOX(cajav_informacion), label_titulo);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_informacion), linea);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_informacion), cajah_fichas);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_informacion), linea2);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_informacion), cajah_undo);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_informacion), linea3);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_informacion), cajah_tiempo);

  //Nombres
  gtk_box_pack_start_defaults(GTK_BOX(cajah_nombres), label_nombre1);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_nombres), label_ficha_color1);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_nombres), label_nombre2);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_nombres), label_ficha_color2);
 
  //Principal
  gtk_box_pack_start_defaults(GTK_BOX(cajah_principal), cajav_tablero);
  gtk_box_pack_start_defaults(GTK_BOX(cajah_principal), cajav_informacion);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_global), cajah_principal);
  gtk_box_pack_start_defaults(GTK_BOX(cajav_global), cajah_nombres);
  gtk_container_add(GTK_CONTAINER(ventana_juego), cajav_global);

  g_object_set_data(G_OBJECT(ventana_juego), "tabla", tablero);

  //5. Mostrar widgets
  gtk_widget_show_all(ventana_juego);

  g_timeout_add_seconds(1, update_time_label2, label);
}

void button_clicked2(GtkWidget *widget, gpointer data)
{

  gchar (*matriz)[20] = data;
  
  gint row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "row"));
  gint column = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "column"));
  GtkWidget *ventana_juego = gtk_widget_get_toplevel(widget);
  gint *contador_X = g_object_get_data(G_OBJECT(ventana_juego), "contador_X");
  gint *contador_O = g_object_get_data(G_OBJECT(ventana_juego), "contador_O");
  GtkWidget *botones[20][20];
  gchar player;
     
  if (matriz[row][column] == '.')
    {
      player = 'X';//ya que el jugador es solo uno
      
      matriz[row][column] = player;
      color_boton2(widget, player);
      
      (*contador_X)++;
      
      if (verifica_5_2(matriz, player))
	{
	  pantalla_ganador(NULL, player);
	}
      
      if (verificador_4_2(matriz, player) >= 5)
	{
	  pantalla_ganador(NULL, player);
	}
      
      if (verifica_5_2(matriz, player) != 1)
	{  
	  hacer_movimiento_cpu(matriz, widget);
	}
      
      g_print("Coordenadas: (%d, %d)\n", row, column);
      imprime2(matriz);
      
    }
  
  //empezamos el algoritmo para eliminar piezas comidas
  if(column >= 3)
    {
      if(verificar_encerradas_hi2(matriz, row, column) > 0)
	{
	  matriz[row][column - 1] = '.';
	  matriz[row][column - 2] = '.';
	}//verificamos si horizontalmente hacia la izquierda hay fichas atrapadas y si las hay las eliminamos de la matriz
    }
  
  if(column <= 17)
    {  
      if(verificar_encerradas_hd2(matriz, row, column) > 0)
	{
	  matriz[row][column + 1] = '.';
	  matriz[row][column + 2] = '.';
	}//verificamos si horizontalmente hacia la izquierda hay fichas atrapadas y si las hay las eliminamos de la matriz
    }
  
  if(column <= 17)
    {
      if(verificar_encerradas_hd2(matriz, row, column) > 0)
	{
	  matriz[row][column + 1] = '.';
	  matriz[row][column + 2] = '.';
	}
    }//verificamos horizontal derecha
  
  if(column >= 3 && row <= 17)
    {
      if(verificar_encerradas_diagonal_abiz2(matriz, row, column) > 0)
	{
	  matriz[row + 1][column - 1] = '.';
	  matriz[row + 2][column - 2] = '.';
	}//verificamos si diagonal abajo hacia la izquierda hacia la izquierda hay fichas atrapadas y si las hay las eliminamos de la matriz	  
	     }
  
  if(column >= 3 && row >= 3)
    {
      if(verificar_encerradas_diagonal_arr_iz2(matriz, row, column) > 0)
	{
	  matriz[row - 1][column - 1] = '.';
	  matriz[row - 2][column - 2] = '.';
	}//verificamos si diagonal arriba hacia la izquierda hay fichas atrapadas y si las hay las eliminamos de la matriz	
	     }
  
  if(column <= 17 && row >= 3) //2
    {
      if(verificar_encerradas_diagonal_arrd2(matriz, row, column) > 0)
	{
	  matriz[row - 1][column + 1] = '.';
	  matriz[row - 2][column + 2] = '.';
	}//verificamos si diagonal abajo hacia la izquierda hacia la izquierda hay fichas atrapadas y si las hay las eliminamos de la matriz	  
	     }
  
  if(column <= 17 && row <= 17)
    {
      if(verificar_encerradas_diagonal_abd2(matriz, row, column) > 0)
	{
	  matriz[row + 1][column + 1] = '.';
	  matriz[row + 2][column + 2] = '.';
	}//verificamos si diagonal arriba hacia la izquierda hay fichas atrapadas y si las hay las eliminamos de la matriz	
	     }//2
  
  
  if(row >=3)
    {
      if(verificar_encerradas_v_arriba2(matriz, row, column) > 0)
	{
	  matriz[row - 1][column] = '.';
	  matriz[row - 2][column] = '.';
	}
    }//verificamos vertical arriba
  
  if(row <= 17)
    {
      if(verificar_encerradas_v_abajo2(matriz, row, column) > 0)
	{
	  matriz[row + 1][column] = '.';
	  matriz[row + 2][column] = '.';
	}
    }//verificamos vertical abajo	       
	 g_print("Coordenadas: (%d, %d)\n", row, column);
  imprime2(matriz);
}

void color_boton2(GtkWidget *widget, gchar player)
{
  if (player == 'X')
    {
      gtk_button_set_label(GTK_BUTTON(widget), "⚫"); // Bola negra para el jugador 'X'
    }
  else if (player == 'O')
    {
      gtk_button_set_label(GTK_BUTTON(widget), "⚪"); // Bola blanca para el jugador 'O'
    }
  else
    {
      gtk_button_set_label(GTK_BUTTON(widget), "");
    }
}


static gboolean update_time_label2(gpointer data)
{
  //Timer
  static int sec_expired = 0;
  GtkLabel *label = GTK_LABEL(data);
  int minutes = sec_expired / 60;
  int seconds = sec_expired % 60;
  char buf[256];
  snprintf(buf, 255, "%02d:%02d", minutes, seconds);
  gtk_label_set_label(label, buf);
  sec_expired++;
  return TRUE;
}

void imprime2(gchar matriz[20][20]){
  gint x, y;
  
  for(x = 0; x < 20; x++)
    {
      for(y = 0; y < 20; y++)
	{
	  g_print("%c", matriz[x][y]);
	  g_print("  ");
	}
      g_print("\n");
    }
}

int verifica_5_2(gchar matriz[20][20], char check) //funcion para checar si existe una linea recta de 5 en el programa
{
  int count;
  // Verificar horizontalmente
  for (int i = 0; i < 20; i++)
    {
      for (int j = 0; j <= 15; j++) // Solo hasta la columna 15
	{
	  count = 0;
	  for (int k = 0; k < 5; k++)
	    {
	      if (matriz[i][j + k] == check)
		{
		  count++;
		}
	    }
	  if (count == 5) return 1;
	}
    }
  
  // Verificar verticalmente
  for (int j = 0; j < 20; j++)
    {
      for (int i = 0; i <= 15; i++)
	{
	  count = 0;
	  for (int k = 0; k < 5; k++)
	    {
	      if (matriz[i + k][j] == check)
		{
		  count++;
		}
	    }
	  if (count == 5) return 1;
	}
    }
  
  // Verificar diagonal principal
  for (int i = 0; i <= 15; i++)
    {
      for (int j = 0; j <= 15; j++)
	{
	  count = 0;
	  for (int k = 0; k < 5; k++)
	    {
	      if (matriz[i + k][j + k] == check)
		{
		  count++;
		}
	    }
	  if (count == 5) return 1;
  	}
    }
  
  // Verificar diagonal secundaria
  for (int i = 0; i <= 15; i++)
    {
      for (int j = 4; j < 20; j++)
	{
	  count = 0;
	  for (int k = 0; k < 5; k++)
	    {
	      if (matriz[i + k][j - k] == check)
		{
		  count++;
		}
	    }
	  if (count == 5) return 1;
  	}
    }
  
  return 0; // Si no se encuentra ninguna línea de cinco
}

int verificador_4_2(gchar matriz[20][20], char check) //funcion que cuenta el numero de lineas rectas echas y condicionamos para verificar si es igual a 4
{
  int cuenta, lineas_totales = 0;
  
  // Verificar horizontalmente
  for (int i = 0; i < 20; i++)
    {
      for (int j = 0; j <= 16; j++) // Revisar hasta la columna 16 para líneas de cuatro
	{
	  cuenta = 0;
	  for (int k = 0; k < 4; k++)
	    {
	      if (matriz[i][j + k] == check)
		{
		  cuenta++;
		}
	    }
	  if (cuenta == 4)
	    {
	      lineas_totales++;
	      j += 3; // Saltar al final de la línea encontrada para evitar contar superposiciones
	    }
	}
    }
  
  // Verificar verticalmente
  for (int j = 0; j < 20; j++)
    {
      for (int i = 0; i <= 16; i++)
	{
	  cuenta = 0;
	  for (int k = 0; k < 4; k++)
	    {
	      if (matriz[i + k][j] == check)
		{
		  cuenta++;
		}
	    }
	  if (cuenta == 4)
	    {
	      lineas_totales++;
	      i += 3; // Saltar al final de la línea encontrada
	    }
	}
    }
  
  // Verificar diagonal principal
  for (int i = 0; i <= 16; i++)
    {
    for (int j = 0; j <= 16; j++)
      {
  	cuenta = 0;
  	for (int k = 0; k < 4; k++)
	  {
	    if (matriz[i + k][j + k] == check)
	      {
		cuenta++;
	      }
	  }
  	if (cuenta == 4)
	  {
	    lineas_totales++;
	    i += 3; // Saltar al final de la línea encontrada
	  }
      }
    }
  
  // Verificar diagonal secundaria
  for (int i = 0; i <= 16; i++)
    {
      for (int j = 3; j < 20; j++)
	{
	  cuenta = 0;
	  for (int k = 0; k < 4; k++)
	    {
	      if (matriz[i + k][j - k] == check)
		{
		  cuenta++;
		}
	    }
	  if (cuenta == 4) {
	    lineas_totales++;
	    i += 3; // Saltar al final de la línea encontrada
	  }
	}
    }
  
  return lineas_totales;
}

void instrucciones2(GtkWidget *boton_reglas, gpointer data)
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

void informacion2(GtkWidget *boton_creditos, gpointer data)
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

int verificar_encerradas_hi2(gchar matriz[20][20], gint row, gint column) {

  char bola = matriz[row][column];
  
  char oponente;

  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
    int encerradas = 0;

      if (matriz[row][column - 1] == oponente && matriz[row][column - 2] == oponente && matriz[row][column - 3] == bola)
	{
	  encerradas++;  
	}
      
      return encerradas;
}

int verificar_encerradas_hd2(gchar matriz[20][20], gint row, gint column)
{
    char bola = matriz[row][column];
  
  char oponente;

  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
  int encerradas = 0;
  
  if (matriz[row][column + 1] == oponente && matriz[row][column + 2] == oponente && matriz[row][column + 3] == bola)
    {
      encerradas++;  
    }
  
  return encerradas;
}

int verificar_encerradas_v_arriba2(gchar matriz[20][20], gint row, gint column)
{
  char bola = matriz[row][column];
  
  char oponente;
  
  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
  int encerradas = 0;
  
  if (matriz[row - 1][column] == oponente && matriz[row - 2][column] == oponente && matriz[row - 3][column] == bola)
    {
      encerradas++;  
    }
  
  return encerradas;
}

int verificar_encerradas_v_abajo2(gchar matriz[20][20], gint row, gint column)
{
  char bola = matriz[row][column];
  
  char oponente;
  
  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
  int encerradas = 0;
  
  if (matriz[row + 1][column] == oponente && matriz[row + 2][column] == oponente && matriz[row + 3][column] == bola)
    {
      encerradas++;  
    }
  
  return encerradas;
}

int verificar_encerradas_diagonal_arrd2(gchar matriz[20][20], gint row, gint column) {
  
  char bola = matriz[row][column];
  
  char oponente;
  
  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
  int encerradas = 0;
  
  if (matriz[row - 1][column + 1] == oponente && matriz[row - 2][column + 2] == oponente && matriz[row - 3][column + 3] == bola)
    {
      encerradas++;  
    }
  
  return encerradas;
}

int verificar_encerradas_diagonal_arr_iz2(gchar matriz[20][20], gint row, gint column)
{  
  char bola = matriz[row][column];
  
  char oponente;
  
  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
  int encerradas = 0;
  
  if (matriz[row - 1][column - 1] == oponente && matriz[row - 2][column - 2] == oponente && matriz[row - 3][column - 3] == bola)
    {
      encerradas++;  
    }
  
  return encerradas;
}

int verificar_encerradas_diagonal_abd2(gchar matriz[20][20], gint row, gint column)
{  
  char bola = matriz[row][column];
  
  char oponente;
  
  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
  int encerradas = 0;
  
  if (matriz[row + 1][column + 1] == oponente && matriz[row + 2][column + 2] == oponente && matriz[row + 3][column + 3] == bola)
    {
      encerradas++;  
    }
  
  return encerradas;
}

int verificar_encerradas_diagonal_abiz2(gchar matriz[20][20], gint row, gint column)
{
  char bola = matriz[row][column];
  
  char oponente;
  
  if(bola == 'X')
    {
      oponente = 'O';
    }
  else
    {
      oponente = 'X';
    }//condicional para verificar quien es el jugador y quien es el oponente
  
  int encerradas = 0;
  
  if (matriz[row + 1][column - 1] == oponente && matriz[row + 2][column - 2] == oponente && matriz[row + 3][column - 3] == bola)
    {
      encerradas++;  
    }
  
  return encerradas;
}

gboolean cerrar_fenetre2(GtkWidget *widget, GdkEvent *event, gpointer data)
{
  return TRUE;
}

void hacer_movimiento_cpu(gchar matriz[20][20], GtkWidget *widget)
{
  int intentos = 0;  // Para evitar bucles infinitos
    srand(time(NULL));  // Inicialización del generador de números aleatorios

    while (intentos < 400)
      {  // Intenta hasta un número máximo de veces
        int i = rand() % 20;  // Genera una posición aleatoria i
        int j = rand() % 20;  // Genera una posición aleatoria j

        if (matriz[i][j] == '.')
	  {  // Chequea si la posición está vacía
            matriz[i][j] = 'O';  // Coloca la ficha de la CPU
            GtkWidget *boton_cpu = buscar_boton_por_posicion(i, j, widget);
            if (boton_cpu != NULL)
	      {
                color_boton2(boton_cpu, 'O');
                gint *contador_O = g_object_get_data(G_OBJECT(gtk_widget_get_toplevel(widget)), "contador_O");
                (*contador_O)++;
                if (verifica_5_2(matriz, 'O'))
		  {
                    pantalla_ganador(NULL, 'O');
		  }
                return;
	      }
	  }
        intentos++;
      }
}

GtkWidget* buscar_boton_por_posicion(int i, int j, GtkWidget *widget)
{
  GtkWidget *ventana_juego = gtk_widget_get_toplevel(widget);
  GtkWidget *tabla = g_object_get_data(G_OBJECT(ventana_juego), "tabla");
  GList *children = gtk_container_get_children(GTK_CONTAINER(tabla));
  GtkWidget *boton_cpu = NULL;
  
  // Calcula el índice del botón en la lista, asumiendo que se agregaron de izquierda a derecha, fila por fila
  int index = i * 20 + j;
  GList *node = g_list_nth(children, index);
  if (node != NULL)
    {
      boton_cpu = (GtkWidget *)node->data;
    }
  g_list_free(children);
  return boton_cpu;
}


