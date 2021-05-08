#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

#include <future>
#include <gtk/gtk.h>
#include <glib.h>
#include <webkit2/webkit2.h>


static gchar* url;
static gchar* screenshotFullPath;

static GOptionEntry entries[] =
{
  { "url", 'u', -1, G_OPTION_ARG_STRING, &url, "Url of website", NULL },
  { "screenshotFullPath", 's', -1, G_OPTION_ARG_STRING, &screenshotFullPath, "Full path of where screenshot should be saved", NULL },
  { NULL }
};


static void
getScreenshotFunction(GObject *object,
                     GAsyncResult *result,
                     gpointer data)
{
    WebKitWebView * webview = (WebKitWebView*)data;
    GError* error = NULL;
	cairo_surface_t* surface = webkit_web_view_get_snapshot_finish(webview, result, &error);
    printf("Writing screenshot to: %s", screenshotFullPath);
	cairo_surface_write_to_png(surface, screenshotFullPath);
    gtk_main_quit();
    
}

static int startScreenshot(gpointer webView) {
    printf("Waiting for load: %f\n", webkit_web_view_get_estimated_load_progress((WebKitWebView*)webView));

    if (webkit_web_view_get_estimated_load_progress((WebKitWebView*)webView) == 1) {
        webkit_web_view_get_snapshot((WebKitWebView *)webView,
                                     WEBKIT_SNAPSHOT_REGION_FULL_DOCUMENT,
                                     WEBKIT_SNAPSHOT_OPTIONS_NONE,
                                     NULL,
                                     getScreenshotFunction,
                                     (WebKitWebView *)webView);
                                     return 0;
    }

    return -1;
}

int main(int argc, char* argv[])
{
    GError *error = NULL;
    GOptionContext *gcontext;

    gcontext = g_option_context_new("- test tree model performance");
    g_option_context_add_main_entries(gcontext, entries, NULL);
    g_option_context_add_group(gcontext, gtk_get_option_group(TRUE));
    if (!g_option_context_parse(gcontext, &argc, &argv, &error))
    {
        g_print("option parsing failed: %s\n", error->message);
        exit(1);
    }

    g_print("Run with arguments:\n");
    g_print("url: %s\n", url);
    g_print("screenshotFullPath: %s\n", screenshotFullPath);

    gtk_init(&argc, &argv);

    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 900, 600);

    WebKitWebContext* context = webkit_web_context_get_default();
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new_with_user_content_manager(webkit_user_content_manager_new()));

    GtkWidget *scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), GTK_WIDGET(webView));
    gtk_container_add(GTK_CONTAINER(main_window), scrolledWindow);
    webkit_web_view_load_uri(webView, url);
    gtk_widget_grab_focus(GTK_WIDGET(webView));
    gtk_widget_show_all(main_window);

    g_timeout_add_seconds(1, startScreenshot, webView);

    gtk_main();


    return 0;
}