/*
	AWFont : Orginal version created by Andrew Williams - University of Bolton

	Do what you like with the program, but please include your
	sourcecode with any distribution and retain these comments

	Version 2.01
	Changes made in V2.00
	All calls to snprintf have been changed to snprintf_s this version is used to
	prevent buffer over/under-runs so is more secure and stops some annoying
	warnings during compilation.
	of this function
	Changes made in V1.02
	Methods added to display floating point numbers and to calculate the display
	lengths of strings, integers and fp numbers. - Stephen Phillips (2009)
	Changes made in V1.01
	Destructor added to fix memory leak - Chris Pepper (2008)

	*/

#ifndef __AWFONTINCLUDED__

#define __AWFONTINCLUDED__  (1)

#include "stdio.h"
#include "SDL.h"
#include <fstream>
using namespace std;

class AWFont {
private:
	char charWidths[256];
	SDL_Surface *fontSurface;

public:
	AWFont::AWFont(char *bmpName, char *widthsName) {
		int transparentColour;
		/* load bitmap to temp surface */
//		SDL_Surface* temp = SDL_LoadBMP(bmpName);	//****
//		/* convert bitmap to display format */
//		fontSurface = SDL_DisplayFormat(temp);
//		SDL_FreeSurface(temp);
//		SDL_Surface *onto = SDL_GetVideoSurface();
	
		fontSurface = SDL_LoadBMP(bmpName);	//****
//		fontSurface = IMG_Load(bmpName);	//****
//		SDL_Surface* onto = SDL_GetWindowSurface(GameBase::window);
//		transparentColour = SDL_MapRGB(onto->format, 0, 0, 0);
//		SDL_SetColorKey(fontSurface, (SDL_SRCCOLORKEY | SDL_RLEACCEL), transparentColour);
		SDL_SetColorKey(fontSurface, SDL_TRUE, SDL_MapRGB(fontSurface->format, 0, 0, 0));

		ifstream widthsFile(widthsName, ios::in | ios::binary);
		widthsFile.read(charWidths, 256);
		if (!widthsFile) {
			// Something wrong with the widths file, so we
			//  default every letter to be 16 pixels wide
			int i;
			for (i = 0; i < 256; i++) {
				charWidths[i] = 16;
			}
		}
//		SDL_FreeSurface(onto);
	}

	// Thanks to Chris Pepper for spotting the memory leak
	AWFont::~AWFont()
	{
		SDL_FreeSurface(fontSurface);
	}

	/*		========== Get Length functions by S. Phillips ==========
	 *		Functions to get lengths of strings, ints and floats,
	 *		could be used for type formatting or aligning text, etc.
	 *		=========================================================
	 */

	int AWFont::getStringLength(const char *string)
	{
		int length = 0;						//length becomes similar to "to.x" in print functions
		int c = 0;							// but it may be necessary to know the length before
		char ch;							// it is printed
		while (string[c] != 0)				// (i.e. when deciding where to print the text)
		{
			ch = string[c];
			length += charWidths[ch];
			c++;
		}
		return length;
	}

	int AWFont::getIntegerLength(int number)
	{
		char buffer[32];
		_snprintf_s(buffer, 32, "%d", number);
		return getStringLength(buffer);
	}

	int AWFont::getFloatLength(float number)
	{
		char buffer[32];
		_snprintf_s(buffer, 32, "%2.2f", number);
		return getStringLength(buffer);
	}

	int AWFont::getFloatLength(float number, char *format)
	{
		char buffer[32];
		_snprintf_s(buffer, 32, format, number);
		return getStringLength(buffer);
	}

	/*		End of Get Length functions
	 *			- S. Phillips		#0710108
	 */

	int AWFont::print_string(const char *string, int X, int Y, SDL_Surface *onto) {
		SDL_Rect from;
		SDL_Rect to;
		int c = 0;
		char ch;

		to.x = X;
		to.y = Y;
		to.w = 16;
		to.h = 16;
		from.w = 16;
		from.h = 16;
		SDL_Texture *texture = SDL_CreateTextureFromSurface(GameBase::renderer, fontSurface);
		while (string[c] != 0) {
			ch = string[c];
			from.x = 16 * (ch % 16);
			from.y = 16 * (ch / 16);
//			SDL_BlitSurface(fontSurface, &from, onto, &to);

			to.w = from.w; to.h = from.h;	//****
//			SDL_Texture *texture = SDL_CreateTextureFromSurface(GameBase::renderer, fontSurface);
			SDL_RenderCopy(GameBase::renderer, texture, &from, &to);
			//SDL_DestroyTexture(texture);
			//texture = NULL;

			to.x = to.x + charWidths[ch];
			c++;
		}
		SDL_DestroyTexture(texture);
		texture = NULL;
		return to.x;
	}

	int AWFont::print_string(const char *string, int X, int Y) {
//		SDL_Surface *onto = SDL_GetVideoSurface();
//		SDL_Surface* onto = SDL_GetWindowSurface(GameBase::window);
//		return this->print_string(string, X, Y, onto);
		return this->print_string(string, X, Y, NULL);
	}

	int AWFont::print_integer(int number, int X, int Y, SDL_Surface *onto) {
		char buffer[32];
		_snprintf_s(buffer, 32, "%d", number);
		return print_string(buffer, X, Y, onto);
	}

	int AWFont::print_integer(int number, int X, int Y) {
		char buffer[32];
		_snprintf_s(buffer, 32, "%d", number);
		return print_string(buffer, X, Y);
	}

	/*		========== Print Float functions by S. Phillips ==========
	 *		Functions for printing floats in the same manner as ints
	 *		and strings. Format can be specified or assumed as "2.2f"
	 */

	int AWFont::print_float(float number, int X, int Y, SDL_Surface *onto) {
		char buffer[32];
		_snprintf_s(buffer, 32, "%2.2f", number);
		return print_string(buffer, X, Y, onto);
	}

	int AWFont::print_float(float number, int X, int Y) {
		char buffer[32];
		_snprintf_s(buffer, 32, "%2.2f", number);
		return print_string(buffer, X, Y);
	}

	int AWFont::print_float(float number, int X, int Y, char *format) {
		char buffer[32];
		_snprintf_s(buffer, 32, format, number);
		return print_string(buffer, X, Y);
	}

	/*		End of Print Float functions
	 *			- S. Phillips		#0710108
	 */
};
#endif
