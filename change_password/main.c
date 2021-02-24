#include <gtk/gtk.h>
static void load_css(void)
{
	GtkCssProvider * provider;
	GdkDisplay * display;
	GdkScreen * screen;
	const gchar *css_style_file = "style.css";
	GFile *css_fp = g_file_new_for_path(css_style_file);
	GError *error = 0;
	provider = gtk_css_provider_new();
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_file(provider, css_fp, &error);
	g_object_unref(provider);
}
static void activate(GtkApplication *app, gpointer data)
{
    load_css();
    GtkWidget *window;
    GtkWidget *oldPasswordChangeLabel, *newPasswordChangeLabel, *confirmNewPasswordChangeLabel;
    GtkWidget *backButton;
    GtkWidget *oldPasswordChangeEntry, *newPasswordChangeEntry, *confirmNewPasswordChangeEntry;

    GtkWidget *updateChangePasswordButton;
    GtkWidget *gridChangePassword;

    //set up
    gridChangePassword = gtk_grid_new();
    //
    oldPasswordChangeEntry = gtk_entry_new();
    newPasswordChangeEntry = gtk_entry_new();
    confirmNewPasswordChangeEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(oldPasswordChangeEntry, "Enter your old password");
    gtk_entry_set_placeholder_text(newPasswordChangeEntry, "Enter your new password");
    gtk_entry_set_placeholder_text(confirmNewPasswordChangeEntry, "Enter your new password again");
    //
    oldPasswordChangeLabel = gtk_label_new("Last password: ");
    newPasswordChangeLabel = gtk_label_new("New password: ");
    confirmNewPasswordChangeLabel = gtk_label_new("Confirm new password: ");
    updateChangePasswordButton = gtk_button_new_with_label("Update");
    //
    gtk_entry_set_visibility(oldPasswordChangeEntry, FALSE);
    gtk_entry_set_visibility(newPasswordChangeEntry, FALSE);
    gtk_entry_set_visibility(confirmNewPasswordChangeEntry, FALSE);
    gtk_grid_attach(gridChangePassword, oldPasswordChangeLabel, 0, 0, 1, 1);
    gtk_grid_attach(gridChangePassword, oldPasswordChangeEntry, 1, 0, 1, 1);
    gtk_grid_attach(gridChangePassword, newPasswordChangeLabel, 0, 1, 1, 1);
    gtk_grid_attach(gridChangePassword, newPasswordChangeEntry, 1, 1, 1, 1);
    gtk_grid_attach(gridChangePassword, confirmNewPasswordChangeLabel, 0, 2, 1, 1);
    gtk_grid_attach(gridChangePassword, confirmNewPasswordChangeEntry, 1, 2, 1, 1);
    gtk_grid_attach(gridChangePassword, updateChangePasswordButton, 1, 3, 1, 1);
    gtk_grid_attach(gridChangePassword, )
    gtk_grid_set_column_spacing(gridChangePassword, 10);
    gtk_grid_set_row_spacing(gridChangePassword, 10);
    gtk_widget_set_name(gridChangePassword, "gridChangePassword");
    window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Change Password");
	gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_add(window, gridChangePassword);
	gtk_widget_show_all(window);
}
int main(int argc, char **argv)
{
    GtkAllocation * app;
	int status;
	app = gtk_application_new("app.shopping.cart", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
