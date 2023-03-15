#include <gtk/gtk.h>

GtkWidget *txt;

void end_program(GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit();
}

void copy_text(GtkWidget *wid, gpointer ptr)
{
    const char *input = gtk_entry_get_text(GTK_ENTRY(txt));
    gtk_label_set_text(GTK_LABEL(ptr), input);
}

void check_toggle(GtkWidget *wid, gpointer ptr)
{
    int state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ptr));
    printf("The state of the button is %d\n", state);
}

void check_radio(GtkWidget *wid, gpointer ptr)
{
    const gchar *text = gtk_button_get_label(GTK_BUTTON(wid));
    // Aşağıdaki de aynı işi görürdü. Zira gpointer olarak widget'ın kendisini gönderiyoruz.
    // const gchar *text = gtk_button_get_label(ptr);
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)))
    {
        printf( "%s\n", text);
    }
}

void combo_changed(GtkWidget *wid, gpointer ptr)
{
    int sel = gtk_combo_box_get_active(GTK_COMBO_BOX(ptr));
    gchar *sel_text;
    if (GTK_IS_COMBO_BOX_TEXT(ptr))
    {
        sel_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ptr));
    }
    else
    {
        sel_text = "Object is not a GTK_COMBO_BOX_TEXT.";
    }
    printf("Index: %d, Text: %s\n", sel, sel_text);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Close window");
    g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
    g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
    GtkWidget *lbl = gtk_label_new("My label");
    GtkWidget *btn2 = gtk_button_new_with_label("Copy button");
    g_signal_connect(btn2, "clicked", G_CALLBACK(copy_text), lbl);
    txt = gtk_entry_new();
    GtkAdjustment *adj = gtk_adjustment_new(0, -10, 10, 1, 0, 0);
    GtkWidget *spin_txt = gtk_spin_button_new(adj, 0, 0);
    GtkWidget *chk = gtk_check_button_new_with_label("My check");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(chk), TRUE);
    g_signal_connect(chk, "toggled", G_CALLBACK(check_toggle), chk);
    GtkWidget *rad1 = gtk_radio_button_new_with_label(NULL, "Radio 1");
    GSList *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rad1));
    GtkWidget *rad2 = gtk_radio_button_new_with_label(group, "Radio 2");
    g_signal_connect(rad1, "toggled", G_CALLBACK(check_radio), rad1);
    g_signal_connect(rad2, "toggled", G_CALLBACK(check_radio), rad2);
    GtkWidget *comb = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comb), "Option 1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comb), "Option 2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comb), "Option 3");
    gtk_combo_box_set_active(GTK_COMBO_BOX(comb), 0);
    g_signal_connect(comb, "changed", G_CALLBACK(combo_changed), comb);
    // List stores
    GtkWidget *lbl_ls = gtk_label_new("Combo box with list store:");
    int pos = 0;
    GtkListStore *ls = gtk_list_store_new(1, G_TYPE_STRING);
    gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "İstanbul", -1);
    gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Ankara", -1);
    gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Zonguldak", -1);
    gtk_list_store_insert_with_values(ls, NULL, pos++, 0, "Kayseri", -1);
    GtkWidget *comb_ls = gtk_combo_box_new_with_model(GTK_TREE_MODEL(ls));
    GtkCellRenderer *rend = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(comb_ls), rend, FALSE);
    gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(comb_ls), rend, "text", 0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comb_ls), 0);
    g_signal_connect(comb_ls, "changed", G_CALLBACK(combo_changed), comb_ls);
    // Sorted list store
    GtkWidget *lbl_sorted_ls = gtk_label_new("Combo box with sorted list store:");
    GtkTreeModelSort *sorted = GTK_TREE_MODEL_SORT(gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(ls)));
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(sorted), 0, GTK_SORT_ASCENDING);
    GtkWidget *comb_sorted_ls = gtk_combo_box_new_with_model(GTK_TREE_MODEL(sorted));
    GtkCellRenderer *rend2 = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(comb_sorted_ls), rend2, FALSE);
    gtk_cell_layout_add_attribute(GTK_CELL_LAYOUT(comb_sorted_ls), rend2, "text", 0);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comb_sorted_ls), 0);
    g_signal_connect(comb_sorted_ls, "changed", G_CALLBACK(combo_changed), comb_sorted_ls);


    GtkWidget *grd = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grd), lbl, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), btn, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), txt, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), spin_txt, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), chk, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), rad1, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), rad2, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grd), comb, 0, 4, 2, 1);
    gtk_grid_attach(GTK_GRID(grd), lbl_ls, 0, 5, 2, 1);
    gtk_grid_attach(GTK_GRID(grd), comb_ls, 0, 6, 2, 1);
    gtk_grid_attach(GTK_GRID(grd), lbl_sorted_ls, 0, 7, 2, 1);
    gtk_grid_attach(GTK_GRID(grd), comb_sorted_ls, 0, 8, 2, 1);
    gtk_container_add(GTK_CONTAINER(win), grd);
    gtk_widget_show_all(win);
    gtk_main();
}
