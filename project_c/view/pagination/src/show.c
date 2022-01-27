#include <ncurses.h>
#include <unistd.h>   /* isatty() */
#include <stdio.h>    /* fileno() */
#include <string.h>   /* strlen() */

#include "../includes/show.h"
#include "../../../model/table/includes/search.h"

#define KEY_ESC 27

#define	PREVIOUS_PAGE 0
#define	NEXT_PAGE  1
#define	JUMP_TO_PAGE  2
#define	DETAILS  3
#define	EXIT  4

typedef struct win_info {
	int height;
	int width;
	int startx;
	int starty;
	int rows;
} * WIN_INFO;

typedef struct page_rows {
	WINDOW * w;
	WIN_INFO wf;
	HEADER header;
	int fields;
	int table_size;
	int page;
	int node_number;
} * PAGE_ROWS;

typedef struct p_fmt_aux {
	int * types;
	int n_fields;
	FILE * fp;
	const char * delim;
} * P_FMT_AUX;

static void destroy_window (WINDOW * w) {
	delwin (w);
}

static void insert_header (WINDOW * w, WIN_INFO wf, TABLE * t) {
	
	HEADER header = get_headers (t);

	char ** header_names = get_header_names (header, get_fields (t));
	char * header_name = NULL;
	int header_name_size = 0;
	int space_from_column = 0;

	int startx = wf->startx;
	int starty = wf->starty;
	int width_column = wf->width / get_fields (t);
	

	init_pair (4, COLOR_BLACK, COLOR_YELLOW);
	wattron (w, COLOR_PAIR (4));

	for (int i = 0; i < get_fields (t); i++) {
		header_name = header_names[i];
		header_name_size = strlen (header_name);
		space_from_column = (width_column - header_name_size) / 2;
		
		mvwprintw(w, starty - 1, startx + space_from_column + (i * width_column), "%s", header_name);
	}

	wattroff (w, COLOR_PAIR (4));
	wrefresh (w);
}

int show_page_rows (tpointer key, tpointer value, tpointer user_data) {
	
	PAGE_ROWS pr = (PAGE_ROWS) user_data;

	WINDOW * w = pr->w;
	
	WIN_INFO wf = pr->wf;
	int rows = wf->rows;
	int startx = wf->startx;
	int starty = wf->starty;
	
	int table_size = pr->table_size;
	int page = pr->page;
	int node_number = pr->node_number;
	int fields = pr->fields;
	HEADER header = pr->header;

	ROW row = (ROW) value;

	if ((page * rows) > table_size) return 1;

	if ((page * rows) > node_number) {pr->node_number++;return 0;}

	if ((page * rows) <= node_number && ((page * rows) + rows) < node_number) return 1;
	
	if ((page * rows) <= node_number && ((page * rows) + rows) > node_number) {
	
		init_pair (6, COLOR_CYAN, COLOR_BLACK);
		init_pair (5, COLOR_WHITE, COLOR_BLACK);
		wattron (w, COLOR_PAIR (5));

		void * content;
		int * type_headers = get_header_types (header, fields);
		int type;
		int width_column = wf->width / fields;

		for (int i = 0; i < fields; i++) {
			type = type_headers[i];
			content = get_row_content_by_column (row,i);
	
			switch (type) {
				case COL_TYPE_INT:
					mvwprintw(w, starty + 1 + 2*(node_number - (page * rows)), startx + (i * width_column), "%d", * (int *) content);
					break;
				case COL_TYPE_FLOAT:
					mvwprintw(w, starty + 1 + 2*(node_number - (page * rows)), startx + (i * width_column), "%f", * (float *) content);
					break;
				case COL_TYPE_STRING:
					if (i == 0) wattron (w, COLOR_PAIR (6) | A_UNDERLINE);
					mvwprintw(w, starty + 1 + 2*(node_number - (page * rows)), startx + (i * width_column), "%s", * (char **) content);
					if (i == 0) {wattroff(w, COLOR_PAIR(6) | A_UNDERLINE);wattron (w, COLOR_PAIR (5));}
					break;
				default:
					break;
			}
		}

		pr->node_number++;
		return 0;
	}

	return 0;
}

static void print_menu (WINDOW * w, WIN_INFO wf, int select, char ** choices, int n_choices) {

	int width_column = (wf->width / n_choices);
	int startx = wf->startx + width_column/2;
	
	box (w, 0, 0);
	wrefresh (w);

	for (int i = 0; i < n_choices; i++) {
		if (i == select) {
			wattron (stdscr, A_REVERSE);
			mvwprintw(stdscr, wf->starty + 1, startx + i*width_column , "%s", choices[i]);
			wattroff (stdscr, A_REVERSE | A_UNDERLINE);
		} else {
			mvwprintw(stdscr, wf->starty + 1, startx + i*width_column, "%s", choices[i]);
		}
	}
	wrefresh (stdscr);
}

static int menu (WINDOW * w, WIN_INFO wf, int * select) {
	WINDOW * menu;

	char *choices[] = {
		"PREVIOUS PAGE",
		"NEXT PAGE",
		"JUMP TO PAGE",
		"DETAILS",
		"EXIT",
	};
	
	menu = newwin (3, wf->width, wf->height + wf->starty, wf->startx);
	keypad (menu, TRUE);

	WIN_INFO wfmenu = malloc (sizeof (struct win_info));
	wfmenu->startx = wf->startx;
	wfmenu->starty = wf->starty + wf->height;
	wfmenu->width = wf->width;

	print_menu (menu, wfmenu, *select, choices, 5);

	int c;
	int enter_key  = 0;

	while (!enter_key) {
		c = wgetch (menu);
		switch (c) {
			case KEY_RIGHT:
				if (*select < 4) *select = *select + 1;
				else *select = 0;
				break;
			case KEY_LEFT:
				if (*select > 0) *select = *select -1;
				else *select = 4;
				break;
			case 0X0A:
				enter_key = 1;
				break;
			case KEY_ESC:
				enter_key = 1;
				*select = 4;
			default:
				break;
		}
		print_menu (menu, wfmenu, *select, choices, 5);	
	}

	wrefresh (menu);
	return *select;
}

static int insert_content (WINDOW * w, WIN_INFO wf, TABLE * t, int page) {
	PAGE_ROWS user_data = malloc (sizeof (struct page_rows));

	user_data->w = w;
	user_data->wf = wf;
	user_data->table_size = table_size (t);
	user_data->page = page;
	user_data->node_number = 0;
	user_data->fields = get_fields (t);
	user_data->header = get_headers (t);
	
	init_pair (11, COLOR_BLACK, COLOR_RED);
	init_pair (12, COLOR_BLACK, COLOR_CYAN);

	if ((page * wf->rows) >= user_data->table_size) {
		attron (COLOR_PAIR (11));
		mvprintw(0, COLS - 20, "PAGE DOES NOT EXIST");
		attroff (COLOR_PAIR (11));
		
		user_data->page--;
		table_search_foreach(t, show_page_rows, (tpointer) user_data);
		return 0;

	} else if (user_data->page < 0) {
		attron (COLOR_PAIR (11));
		mvprintw(0, COLS - 20, "PAGE DOES NOT EXIST");
		attroff (COLOR_PAIR (11));
		
		user_data->page++;
    table_search_foreach(t, show_page_rows, (tpointer) user_data);
		return -1;
	
	} else {

		attron (COLOR_PAIR (12));
		mvprintw(0, COLS - 20, "  PAGE NUMBER [%d]  ", page);
		mvprintw(0, COLS - 40, "TOTAL PAGES: %d", user_data->table_size / wf->rows);
		attroff (COLOR_PAIR (12));
		
		table_search_foreach(t, show_page_rows, (tpointer) user_data);
		wrefresh (w);
		return 1;
	}
}

static WINDOW * create_window (WIN_INFO wf, int n_fields) {
	WINDOW * window;

	int height = wf->height;
	int width = wf->width;
	int startx = wf->startx;
	int starty = wf->starty;

	window = newwin (height, width, starty, startx);
/*	
	box(window, 0, 0);
	
	int i;
	for (i = 0; i < height - 4; i+=2) {
		mvwhline(window , starty + i , startx - 1 , 0, width - 2);
	}

	wf->rows = i/2;
	
	int width_column = width / n_fields;

	for (i = 1; i < n_fields; i++) {
		mvwvline(window , starty - 1 , startx - 1 + (i * width_column)  , 0, height - 2);
	}*/

	return window;
}

void fill_lines (WINDOW * window, WIN_INFO wf, int n_fields) {

	int height = wf->height;
	int width = wf->width;
	int startx = wf->startx;
	int starty = wf->starty;
	
	box(window, 0, 0);
	
	int i;
	for (i = 0; i < height - 4; i+=2) {
		mvwhline(window , starty + i , startx - 1 , 0, width - 2);
	}

	wf->rows = i/2;
	
	int width_column = width / n_fields;

	for (i = 1; i < n_fields; i++) {
		mvwvline(window , starty - 1 , startx - 1 + (i * width_column)  , 0, height - 2);
	}
}

void table_pagination (TABLE * t) {

	/* <ncurses> init routine */
	initscr();

	/* in order to get special characteres */
	keypad(stdscr,TRUE);

	/* in order to get <one-by-one> characteres */
	cbreak();

	/* in order to not show character when inserts */
	noecho();

	/* in order to use color */
	start_color();

	/* create <PAIR_COLORS> */
	init_pair (1, COLOR_BLACK, COLOR_YELLOW);
	init_pair (9, COLOR_BLACK, COLOR_CYAN);
	init_pair (2, COLOR_YELLOW, COLOR_BLACK);
	
	/* print info */
	attron (COLOR_PAIR (1));
	printw ("Press Esc to exit"); 
	attroff (COLOR_PAIR (1));
		
	/* print info */
	attron (COLOR_PAIR (9));
	mvprintw (0, 20, "Use arrows keys to navigate"); 
	attroff (COLOR_PAIR (1));
		
	/* print info */
	attron (COLOR_PAIR(2) | A_UNDERLINE);
	mvprintw (1, COLS/2, "TABLE");
	attroff (COLOR_PAIR (2) | A_UNDERLINE);

	/* show <stdscr> window with <infos> */
	refresh ();

	/* get <n_fields> of the TABLE */
	int n_fields = get_fields (t);

	/* declaration of the <PAGE_WINDOW> */
	WINDOW * window;	
	WIN_INFO wf = malloc (sizeof (struct win_info));
	
	/* fill <PAGE_WINDOW> infos */
	wf->width = COLS - 5;
	wf->height = LINES - 5;
	wf->startx = (COLS - wf->width) / 2;
	wf->starty = (LINES - wf->height) / 2;		

	/* create <PAGE_WINDOW> */
	window = create_window (wf, n_fields);
	int parse_page;
	int ch = 1;
	int * select = malloc (sizeof (int));
	int page = 0;
	*select = 0;

	while (ch != KEY_ESC) {
			
		werase(window);
		wrefresh(window);

		fill_lines (window, wf, n_fields);
		insert_header (window, wf, t);
		
		parse_page = insert_content (window, wf, t, page);

		switch (parse_page) {
			case -1:
				page++;
				break;
			case 0:
				page--;
				break;
			default:
				break;
		}

		wrefresh(window);
			
		ch = menu(window, wf, select);
			
		switch (ch) {
			case PREVIOUS_PAGE:
				page--;
				break;
			case NEXT_PAGE:
				page++;
				break;
			case JUMP_TO_PAGE:
				/* TODO */
				break;
			case DETAILS:
				/* TODO */
				break;
			case EXIT:
					ch = KEY_ESC;
				break;
			default:
					break;
			}
		}

		/* <ncurses> end routine */
		werase (window);
		werase (stdscr);
		destroy_window (window);
		endwin();
		return;
}

int print_line_fmt (tpointer key, tpointer value, tpointer user_data) {

	/* cast <user_data> */
	P_FMT_AUX aux = (P_FMT_AUX) user_data;

	/* get <user_data> info */
	int * types = aux->types;
	int n_fields = aux->n_fields;
	FILE * fp = aux->fp;
	const char * delim = aux->delim;

	/* get actual node (ROW) */
	ROW row = (ROW) value;

	/* write (n-1) fields */
	for (int i = 0; i < n_fields - 1; i++)
		switch (types[i]) {
			case COL_TYPE_INT:
				fprintf (fp,"%d%s", * (int *) get_row_content_by_column(row, i), delim);
				break;
			case COL_TYPE_FLOAT:
				fprintf (fp,"%f%s", * (float *) get_row_content_by_column(row, i), delim);
				break;
			case COL_TYPE_STRING:
				fprintf (fp,"%s%s", * (char **) get_row_content_by_column(row, i), delim);
				break;
			default:
				break;
		}
	
	/* write last field */
	switch (types[n_fields - 1]) {
			case COL_TYPE_INT:
				fprintf (fp,"%d\n", * (int *) get_row_content_by_column(row, n_fields - 1));
				break;
			case COL_TYPE_FLOAT:
				fprintf (fp,"%f\n", * (float *) get_row_content_by_column(row, n_fields - 1));
				break;
			case COL_TYPE_STRING:
				fprintf (fp,"%s\n", * (char **) get_row_content_by_column(row, n_fields - 1));
				break;
			default:
				break;
		}

	return 0;
}

void table_to_file_delim (FILE * fp, TABLE * t, const char * delim) {
	
	/* get header from TABLE */
	HEADER header = get_headers (t);

	/* get number of <fields> from TABLE */
	int n_fields = get_fields (t);

	/* declaration of <user_data> for <foreach> */
	P_FMT_AUX user_data = malloc (sizeof (struct p_fmt_aux));

	/* fill <user_data> */
	user_data->types = get_header_types (header, n_fields);
	user_data->n_fields = n_fields;
	user_data->fp = fp;
	user_data->delim = delim;

	table_search_foreach (t, print_line_fmt, user_data);
}

