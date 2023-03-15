#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void open_my(GtkWidget *wid, gpointer ptr)
{
    GtkWidget *dlg = gtk_dialog_new_with_buttons("My dialog", GTK_WINDOW(ptr), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "Cancel", 0, "OK", 1, NULL);
    GtkWidget *lbl = gtk_label_new("\nQuit without saving?\n\n");
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dlg))), lbl);
    gtk_widget_show(lbl);

    int result = gtk_dialog_run(GTK_DIALOG(dlg));
    gtk_widget_destroy(dlg);
    printf("Return code = %d\n", result);
}

static void file_selected(GtkWidget *wid, gpointer ptr)
{
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(wid));
    printf("File '%s' selected.\n", filename);
}

static void color_selected(GtkWidget *wid, gpointer ptr)
{
    GdkRGBA col;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(wid), &col);
    printf("red = %f, green = %f, blue = %f\n", col.red, col.green, col.blue);

}

static void font_selected(GtkFontChooser *btn, gpointer ptr)
{
    char *font = gtk_font_chooser_get_font(btn);
    printf("Selected font: %s\n", font);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn_my = gtk_button_new_with_label("Open 'My dialog'");
    GtkWidget *btn_fc = gtk_file_chooser_button_new("Bir dosya seçin", GTK_FILE_CHOOSER_ACTION_OPEN);
    GtkWidget *lbl_fc = gtk_label_new("Bir dosya seçin:");
    GtkWidget *btn_col = gtk_color_button_new();
    GtkWidget *lbl_col = gtk_label_new("Bir renk seçin:");
    GtkWidget *btn_fnt = gtk_font_button_new();
    GtkWidget *lbl_fnt = gtk_label_new("Bir font seçin:");

    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
    g_signal_connect(btn_my, "clicked", G_CALLBACK(open_my), win);
    g_signal_connect(btn_fc, "file-set", G_CALLBACK(file_selected), NULL);
    g_signal_connect(btn_col, "color-set", G_CALLBACK(color_selected), NULL);
    g_signal_connect(btn_fnt, "font-set", G_CALLBACK(font_selected), NULL);

    GtkWidget *grd = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grd), btn_my, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), lbl_fc, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn_fc, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), lbl_col, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn_col, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), lbl_fnt, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn_fnt, 1, 3, 1, 1);
    gtk_container_add(GTK_CONTAINER(win), grd);

    gtk_widget_show_all(win);
    gtk_main();
}
