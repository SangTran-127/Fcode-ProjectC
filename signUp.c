/**
 * Demo GTK+ Application that illustrates data entry.
 *
 * M. Horauer
 */
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

typedef struct
{
    GtkWidget *tmpEntry;
    GtkWidget *fnameEntry;
    GtkWidget *gnameEntry;
    GtkWidget *cityEntry;
    GtkWidget *byearSpin;
    GtkWidget *bmonthSpin;
    GtkWidget *bdaySpin;
} diaWidgets;

typedef struct
{
    GtkApplication *app;
    GtkWidget *window;
    GtkWidget *img;
    diaWidgets *d;
} appWidgets;

/***************************************************************** PROTOTYPES */
static void activate_signUp(GtkApplication *app, gpointer user_data);
static void img_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data);
static void cancel_callback(GtkWidget *widget, gpointer user_data);
static void clear_callback(GtkWidget *widget, gpointer user_data);
static void add_callback(GtkWidget *widget, gpointer user_data);
static void get_datestamp(gchar *ds);
static gint get_next_id(void);

/**************************************************************** get_next_id */
static gint
get_next_id(void)
{
    return 12;
}

/************************************************************** get_datestamp */
static void
get_datestamp(gchar *ds)
{
    GTimeVal time;
    GDate date;

    g_get_current_time(&time);
    g_date_clear(&date, 1);
    g_date_set_time_val(&date, &time);
    g_date_strftime(ds, 256, "%F", &date);
}
/**************************************************************** imgCallback */
static void
img_callback(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    GtkWidget *imgDialog;
    GtkFileFilter *filter;
    gint res;
    appWidgets *a = (appWidgets *)user_data;

    filter = gtk_file_filter_new();
    imgDialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(a->window),
                                            GTK_FILE_CHOOSER_ACTION_OPEN,
                                            "_Cancel", GTK_RESPONSE_CANCEL,
                                            "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_filter_add_mime_type(GTK_FILE_FILTER(filter), "image/png");
    gtk_file_filter_add_mime_type(GTK_FILE_FILTER(filter), "image/jpg");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(imgDialog), filter);

    res = gtk_dialog_run(GTK_DIALOG(imgDialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename, *tfilename;
        char ofilename[256] = "";
        GFile *in, *out;
        GtkWidget *image;
        const GdkPixbuf *pb;
        GError **error = NULL;

        GtkFileChooser *chooser = GTK_FILE_CHOOSER(imgDialog);
        filename = gtk_file_chooser_get_filename(chooser);

        // get size of image
        image = gtk_image_new_from_file(filename);
        pb = gtk_image_get_pixbuf(GTK_IMAGE(image));
        /* if size matches w=80 && h=90 copy it to destination and load it */
        if (gdk_pixbuf_get_width(pb) == 80 && gdk_pixbuf_get_height(pb) == 90)
        {
            /* remove the path & add a new default one "./img/" where we store all
           images */
            tfilename = g_strrstr(filename, "/");
            g_sprintf(ofilename, "./img/%s", &tfilename[1]);
            /* copy the image */
            in = g_file_new_for_path(filename);
            out = g_file_new_for_path(ofilename);
            g_file_copy(in, out, G_FILE_COPY_NONE, NULL, NULL, NULL, error);
            gtk_image_set_from_file(GTK_IMAGE(a->img), ofilename);
        }
        else
        {
            gtk_image_set_from_file(GTK_IMAGE(a->img), "src/avatar2.png");
        }
        g_free(filename);
    }
    gtk_widget_destroy(imgDialog);
}

/************************************************************ Cancel Callback */
static void
cancel_callback(GtkWidget *widget, gpointer user_data)
{
    appWidgets *a = (appWidgets *)user_data;

    g_print("Cancel pressed!\n");
    g_application_quit(G_APPLICATION(a->app));
}

/************************************************************* Clear Callback */
static void
clear_callback(GtkWidget *widget, gpointer user_data)
{
    appWidgets *a = (appWidgets *)user_data;

    g_print("Clear pressed!\n");
    gtk_entry_set_text(GTK_ENTRY(a->d->tmpEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a->d->fnameEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a->d->gnameEntry), "");
    gtk_entry_set_text(GTK_ENTRY(a->d->cityEntry), "");
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->byearSpin), 1990);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->bmonthSpin), 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->bdaySpin), 1);
    gtk_image_set_from_file(GTK_IMAGE(a->img), "src/avatar.png");
}

/*************************************************************** Add Callback */
static void
add_callback(GtkWidget *widget, gpointer user_data)
{
    appWidgets *a = (appWidgets *)user_data;

    g_print("Add pressed!\n");
    g_print("-------------------------------\n");
    g_print("Given Name: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->tmpEntry)));
    g_print("Family Name: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->fnameEntry)));
    g_print("Street: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->gnameEntry)));
    g_print("City: %s\n", gtk_entry_get_text(GTK_ENTRY(a->d->cityEntry)));
    g_print("Birth: %.0lf-%.0lf-%.0lf\n",
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a->d->byearSpin)),
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a->d->bmonthSpin)),
            gtk_spin_button_get_value(GTK_SPIN_BUTTON(a->d->bdaySpin)));
    g_print("-------------------------------\n");
}

/********************************************************* nameentry_callback */
static void
nameentry_callback(GtkWidget *widget, gpointer user_data)
{
    gint studyProgNr = 54;
    gchar *org = "uni";
    gchar *cnt = "net";
    gchar *gname, *fname;
    gchar email[256];
    gchar dateStamp[256];
    gchar *year;
    gchar id[256] = "";
    appWidgets *a = (appWidgets *)user_data;

    /* construct the eMail address */
    gname = (gchar *)gtk_entry_get_text(GTK_ENTRY(a->d->tmpEntry));
    fname = (gchar *)gtk_entry_get_text(GTK_ENTRY(a->d->fnameEntry));
    /* we update the fields on the top only when we got a family name */
    if ((g_strcmp0(gname, "") != 0) && (g_strcmp0(fname, "") != 0))
    {
        g_sprintf(email, "%s.%s@%s.%s", gname, fname, org, cnt);
        /* update date info when Family Name was entered */
        get_datestamp(dateStamp);
        /* construct matrnum when Family Name was entered */
        year = g_strndup(dateStamp, 4);
        g_snprintf(id, 10, "%s%d%03d", year, studyProgNr, get_next_id());
    }
}

/***************************************************************** ADD WINDOW */
static void
activate_signUp(GtkApplication *app, gpointer user_data)
{
    GtkWidget *box;
    GtkWidget *ebox;
    GtkWidget *grid;
    GtkWidget *tmpLabel;
    GtkWidget *fnameLabel;
    GtkWidget *gnameLabel;
    GtkWidget *cityLabel;
    GtkWidget *birthLabel;
    GtkWidget *cButton;
    GtkWidget *lButton;
    GtkWidget *aButton;
    appWidgets *a = (appWidgets *)user_data;

    /* create a window with title, default size,and icons */
    a->window = gtk_application_window_new(a->app);
    gtk_window_set_application(GTK_WINDOW(a->window), GTK_APPLICATION(a->app));
    gtk_window_set_title(GTK_WINDOW(a->window), "Student Management Toolbox");
    gtk_window_set_default_size(GTK_WINDOW(a->window), 400, 300);
    gtk_window_set_default_icon_from_file("icon.png", NULL);
    gtk_window_set_resizable(GTK_WINDOW(a->window), FALSE);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    gtk_container_add(GTK_CONTAINER(a->window), GTK_WIDGET(box));
    gtk_container_set_border_width(GTK_CONTAINER(a->window), 10);

    /* grid: image and labels */
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_size_request(GTK_WIDGET(grid), 400, 90);
    gtk_widget_set_valign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(grid), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(grid), TRUE, TRUE, 0);

    /* clickable image top left */
    ebox = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(ebox), 150, 90);
    gtk_widget_set_valign(GTK_WIDGET(ebox), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(ebox), GTK_ALIGN_CENTER);
    a->img = gtk_image_new_from_file("src/avatar.png");
    gtk_container_add(GTK_CONTAINER(ebox), a->img);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(ebox), 1, 0, 1, 3);
    g_signal_connect(G_OBJECT(ebox), "button_press_event",
                     G_CALLBACK(img_callback), (gpointer)a);

    tmpLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Given Name:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(tmpLabel), 0, 3, 1, 1);
    a->d->tmpEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->tmpEntry), 1, 3, 1, 1);

    fnameLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Family Name:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(fnameLabel), 2, 3, 1, 1);
    a->d->fnameEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->fnameEntry), 3, 3, 1, 1);
    g_signal_connect(G_OBJECT(a->d->fnameEntry), "activate",
                     G_CALLBACK(nameentry_callback), (gpointer)a);

    gnameLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Street:",
                                 "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(gnameLabel), 0, 4, 1, 1);
    a->d->gnameEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->gnameEntry), 1, 4, 1, 1);

    cityLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "City:",
                               "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cityLabel), 2, 4, 1, 1);
    a->d->cityEntry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->cityEntry), 3, 4, 1, 1);

    birthLabel = gtk_widget_new(GTK_TYPE_LABEL, "label", "Date of Birth:",
                                "xalign", 1.0, "yalign", 0.5, NULL);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(birthLabel), 0, 6, 1, 1);
    a->d->byearSpin = gtk_spin_button_new_with_range(1900, 2000, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(a->d->byearSpin), 1990);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->byearSpin), 1, 6, 1, 1);
    a->d->bmonthSpin = gtk_spin_button_new_with_range(1, 12, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->bmonthSpin), 2, 6, 1, 1);
    a->d->bdaySpin = gtk_spin_button_new_with_range(1, 31, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(a->d->bdaySpin), 3, 6, 1, 1);

    /* lowerbox: buttons */
    cButton = gtk_button_new_with_mnemonic("_Cancel");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cButton), 1, 7, 1, 1);
    g_signal_connect(G_OBJECT(cButton), "clicked", G_CALLBACK(cancel_callback),
                     (gpointer)a);
    lButton = gtk_button_new_with_mnemonic("C_lear");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(lButton), 2, 7, 1, 1);
    g_signal_connect(G_OBJECT(lButton), "clicked", G_CALLBACK(clear_callback),
                     (gpointer)a);
    aButton = gtk_button_new_with_mnemonic("_Add");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(aButton), 3, 7, 1, 1);
    g_signal_connect(G_OBJECT(aButton), "clicked", G_CALLBACK(add_callback),
                     (gpointer)a);

    /* display all widgets */
    gtk_widget_show_all(GTK_WIDGET(a->window));
}

/*********************************************************************** main */
int main(int argc, char **argv)
{
    int status;
    appWidgets *a = g_malloc(sizeof(appWidgets));
    a->d = g_malloc(sizeof(diaWidgets));

    a->app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(G_OBJECT(a->app), "activate", G_CALLBACK(activate_signUp),
                     (gpointer)a);
    status = g_application_run(G_APPLICATION(a->app), argc, argv);
    g_object_unref(a->app);

    g_free(a->d);
    g_free(a);
    return status;
}
/** EOF */
