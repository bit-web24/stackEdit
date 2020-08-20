#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

gchar *markdown = "Markdown";
gchar FILE_NAME[20];

extern void file_open(GtkWidget *box, gpointer text_view)
{
    GtkWidget *dialog;
    GtkTextBuffer *buffer;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    dialog = gtk_file_chooser_dialog_new("Open File", NULL, action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        FILE *fp;
        char *filename;
        char CH;
        char FILE_CONTENT[1024];
        int counter_1 = 0;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        fp = fopen(filename, "w+");

        while (CH = fgetc(fp) != EOF)
        {
            FILE_CONTENT[counter_1] = CH;
            counter_1 += 1;
        };

        buffer = gtk_text_buffer_new(NULL);
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), FILE_CONTENT, counter_1*sizeof(char));
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(text_view), buffer);

        g_free(filename);
    }
    gtk_widget_destroy(dialog);
};

extern void run_code(GtkWidget *box, gpointer text_view)
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer;
    GtkWidget *label;
    GtkWidget *layout;
    GtkWidget *output_window;
    GtkWidget *header_bar;
    GtkWidget *scrolled_window;

    buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    markdown = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    output_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(output_window), 600, 700);
    gtk_window_set_resizable(GTK_WINDOW(output_window), false);
    gtk_widget_set_name(output_window, "output_window");
    gtk_window_set_position(GTK_WINDOW(output_window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(output_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), true);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Output");
    gtk_window_set_titlebar(GTK_WINDOW(output_window), header_bar);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(output_window), scrolled_window);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), layout);

    label = gtk_label_new(markdown);
    gtk_layout_put(GTK_LAYOUT(layout), label, 10, 10);

    gtk_widget_show_all(output_window);
    g_free(markdown);
};

extern void destroy_widget(GtkWidget *box, gpointer widget)
{
    gtk_widget_destroy(widget);
};

extern void open_about(GtkWidget *box, gpointer data)
{
    GtkWidget *about_window;
    GtkWidget *header_bar;
    GtkWidget *layout;
    GtkWidget *label;
    GtkWidget *image;

    about_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(about_window), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(about_window), false);
    gtk_window_set_position(GTK_WINDOW(about_window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(about_window), "./img/book4.png", NULL);
    g_signal_connect(G_OBJECT(about_window), "destroy", G_CALLBACK(destroy_widget), about_window);

    header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), true);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "About");
    gtk_window_set_titlebar(GTK_WINDOW(about_window), header_bar);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(about_window), layout);

    image = gtk_image_new_from_file("./img/book3.png");
    gtk_layout_put(GTK_LAYOUT(layout), image, 150, 20);

    label = gtk_label_new("StackEdit");
    gtk_widget_set_name(label, "application_name");
    gtk_layout_put(GTK_LAYOUT(layout), label, 160, 170);

    label = gtk_label_new("Version-1.0.0");
    gtk_widget_set_name(label, "application_version");
    gtk_layout_put(GTK_LAYOUT(layout), label, 145, 205);

    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<span>This application is built with</span> <span foreground=\"red\">❤</span> <span>by <b>Bittu</b></span>");
    gtk_widget_set_name(label, "application_developer");
    gtk_layout_put(GTK_LAYOUT(layout), label, 0, 240);

    gtk_widget_show_all(about_window);
};

extern void show_cheat_sheet(GtkWidget *box, gpointer data)
{
    GtkWidget *cheat_sheet_window;
    GtkWidget *cheat_sheet_box;
    GtkWidget *header_bar;
    GtkWidget *label;
    GtkWidget *scrolled_window;

    cheat_sheet_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(cheat_sheet_window, "cheat_sheet_window");
    gtk_window_set_resizable(GTK_WINDOW(cheat_sheet_window), false);
    gtk_window_set_position(GTK_WINDOW(cheat_sheet_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(cheat_sheet_window), 500, 600);
    g_signal_connect(G_OBJECT(cheat_sheet_window), "destroy", G_CALLBACK(destroy_widget), cheat_sheet_window);

    header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), true);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Cheat-Sheet");
    gtk_window_set_titlebar(GTK_WINDOW(cheat_sheet_window), header_bar);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(cheat_sheet_window, "cheat_sheet_scrolled_window");
    gtk_container_add(GTK_CONTAINER(cheat_sheet_window), scrolled_window);

    char *MARKUP = "\n<span size=\"large\" weight=\"heavy\">Headers</span>\n<span>---------------------------</span>\n\n<span size=\"medium\"># Header 1</span>\n\n<span size=\"large\">## Header 2</span>\n\n<span size=\"x-large\">### Header 3</span>\n\n<span size=\"large\" weight=\"heavy\">Styling</span>\n<span>---------------------------</span>\n\n<span>*<i>Emphasize</i>* _<i>emphasize</i>_</span>\n\n<span>**<b>Strong</b>** __<b>strong</b>__</span>\n\n<span>==<span background=\"yellow\">Marked text.</span>==</span>\n\n<span>~~<span strikethrough=\"true\">Mistaken text.</span>~~</span>\n\n<span foreground=\"grey\">> Quoted text.</span>\n\n<span size=\"large\" weight=\"heavy\">Links</span>\n---------------------------\n\nA [<span foreground=\"blue\">link</span>](<span foreground=\"blue\">http://example.com</span>).\n\nAn image: ![Alt](<span foreground=\"blue\">img.jpg</span>)\n\nA sized image: ![Alt]((<span foreground=\"blue\">img.jpg = 60x50</span>)\n\n<span size=\"large\" weight=\"heavy\">Code</span>\n---------------------------\n\nSome `<span background=\"#efefef\" font_family=\"monospace\">inline code</span>`.\n\n```\n<span background=\"#efefef\" font_family=\"monospace\"><span foreground=\"gray\">// A code block </span>\nvar foo = 'bar';</span>\n```\n";
    label = gtk_label_new(NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), label);
    gtk_widget_set_name(label, "cheat_sheet_txt");
    gtk_label_set_markup(GTK_LABEL(label), MARKUP);

    gtk_widget_show_all(cheat_sheet_window);
};