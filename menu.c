#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer *ptr)
{
    gtk_main_quit();
}

void image_popup(GtkWidget *wid, gpointer *ptr)
{
    GtkWidget *f_menu = gtk_menu_new();
    GtkWidget *quit_mi = gtk_menu_item_new_with_label("Quit (on button)");
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
    g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);
    gtk_widget_show_all(f_menu);
    gtk_menu_popup_at_pointer(GTK_MENU(f_menu), gtk_get_current_event());
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

    // Menu bar
    GtkWidget *mbar = gtk_menu_bar_new();
    GtkWidget *file_mi = gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(mbar), file_mi);
    GtkWidget *f_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), f_menu);
    GtkWidget *quit_mi = gtk_menu_item_new_with_label("Quit (on menu)");
    gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
    g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);

    GdkPixbuf *icon = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), "gtk-apply", 32, 0, NULL);
    GtkWidget *img = gtk_image_new_from_pixbuf(icon);
    GtkWidget *lbl = gtk_label_new("It works! Click on the button for pop-up menu.");

    // Pop-up menu signal connect
    g_signal_connect(btn, "clicked", G_CALLBACK(image_popup), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), mbar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), img, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), lbl, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 10);
    gtk_container_add(GTK_CONTAINER(win), vbox);

    gtk_widget_show_all(win);
    gtk_main();
}
