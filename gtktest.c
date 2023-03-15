#include <gtk/gtk.h>

int count = 0;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void count_button(GtkWidget *wid, gpointer ptr)
{
    char buffer[30];
    count++;
    sprintf(buffer, "Button pressed %d times", count);
    gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    GtkWidget *lbl = gtk_label_new("My label");
    GtkWidget *btn2 = gtk_button_new_with_label("Count button");
    g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), lbl);
    // GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    // gtk_box_pack_start(GTK_BOX(box), btn2, TRUE, FALSE, 0);
    // gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(box), btn, TRUE, FALSE, 0);
    // gtk_container_add(GTK_CONTAINER(win), box);
    GtkWidget *grd = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grd), lbl, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn, 0, 1, 2, 1);
    gtk_container_add(GTK_CONTAINER(win), grd);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
