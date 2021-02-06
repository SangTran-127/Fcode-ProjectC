#include <gtk/gtk.h>

static void onClicked(GtkWidget *widget, gpointer data){
    g_print("clicked\n");
}
static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;
    GtkWidget *label;
    GtkWidget *containerBox;
    //create window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    //create label Hello World
    label = gtk_label_new("Hello World");
    //create bottonBox and add buttonLabel into bottonBox
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label("Click Me");
    gtk_container_add(GTK_CONTAINER(button_box), button);
    //create container gtkBox
    containerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    //add label and button_box into gtkBox
    gtk_box_pack_start(containerBox, label, FALSE, FALSE, 50);
    gtk_box_pack_start(containerBox, button_box, FALSE, FALSE, 10);
    //handle click event
    g_signal_connect(button, "clicked", G_CALLBACK(onClicked), NULL);

    gtk_container_add(GTK_CONTAINER(window), containerBox);
    gtk_widget_show_all(window);
}

int main (int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app     = gtk_application_new("hello.world", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
    status  = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;

}
