/***************************************************************************
 *   Copyright (C) 2006 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


/*
 * Include the standard headers for cout to write
 * some output to the console.
 */
#include <iostream>

/*
 * Now include all podofo header files, to have access
 * to all functions of podofo and so that you do not have
 * to care about the order of includes.
 *
 * You should always use podofo.h and not try to include
 * the required headers on your own.
 */
#include <podofo/podofo.h>

/*
 * All podofo classes are member of the PoDoFo namespace.
 */
using namespace PoDoFo;

void HelloWorld( const char* pszFilename )
{
    /*
     * PdfStreamedDocument is the class that can actually write a PDF file.
     * PdfStreamedDocument is much faster than PdfDocument, but it is only
     * suitable for creating/drawing PDF files and cannot modify existing
     * PDF documents.
     *
     * The document is written directly to pszFilename while being created.
     */
    PdfStreamedDocument document( pszFilename );
    /*
     * This pointer will hold the page object later.
     * PdfSimpleWriter can write several PdfPage's to a PDF file.
     */
    PdfPage* pPage;
    /*
     * PdfPainter is the class which is able to draw text and graphics
     * directly on a PdfPage object.
     */
    PdfPainter painter;
    /*
     * A PdfFont object is required to draw text on a PdfPage using a PdfPainter.
     * PoDoFo will find the font using fontconfig on your system and embedd truetype
     * fonts automatically in the PDF file.
     */
    PdfFont* pFont;

    /*
     * The PdfDocument object can be used to create new PdfPage objects.
     * The PdfPage object is owned by the PdfDocument will also be deleted automatically
     * by the PdfDocument object.
     *
     * You have to pass only one argument, i.e. the page size of the page to create.
     * There are predefined enums for some common page sizes.
     */
    pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );

    /*
     * If the page cannot be created because of an error (e.g. ePdfError_OutOfMemory )
     * a NULL pointer is returned.
     * We check for a NULL pointer here and throw an exception using the RAISE_ERROR macro.
     * The raise error macro initializes a PdfError object with a given error code and
     * the location in the file in which the error ocurred and throws it as an exception.
     */
    if( !pPage )
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    /*
     * Set the page as drawing target for the PdfPainter.
     * Before the painter can draw, a page has to be set first.
     */
    painter.SetPage( pPage );

    /*
     * Create a PdfFont object using the font "Arial".
     * The font is found on the system using fontconfig and embedded into the
     * PDF file. If Arial is not available, a default font will be used.
     *
     * The created PdfFont will be deleted by the PdfDocument.
     */
    pFont = document.CreateFont( "Arial" );

    /*
     * If the PdfFont object cannot be allocated return an error.
     */
    if( !pFont )
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    /*
     * Set the font size
     */
    pFont->SetFontSize( 18.0 );

    /*
     * Set the font as default font for drawing.
     * A font has to be set before you can draw text on
     * a PdfPainter.
     */
    painter.SetFont( pFont );

    /*
     * You could set a different color than black to draw
     * the text.
     *
     * SAFE_OP( painter.SetColor( 1.0, 0.0, 0.0 ) );
     */

    /*
     * Actually draw the line "Hello World!" on to the PdfPage at
     * the position 2cm,2cm from the top left corner.
     * Please remember that PDF files have their origin at the
     * bottom left corner. Therefore we substract the y coordinate
     * from the page height.
     *
     * The position specifies the start of the baseline of the text.
     *
     * All coordinates in PoDoFo are in PDF units.
     * You can also use PdfPainterMM which takes coordinates in 1/1000th mm.
     *
     */
    painter.DrawText( 56.69, pPage->GetPageSize().GetHeight() - 56.69, "Hello World!" );

    /*
     * Tell PoDoFo that the page has been drawn completely.
     * This required to optimize drawing operations inside in PoDoFo
     * and has to be done whenever you are done with drawing a page.
     */
    painter.FinishPage();

    /*
     * Set some additional information on the PDF file.
     */
    document.GetInfo()->SetCreator ( PdfString("examplahelloworld - A PoDoFo test application") );
    document.GetInfo()->SetAuthor  ( PdfString("Dominik Seichter") );
    document.GetInfo()->SetTitle   ( PdfString("Hello World") );
    document.GetInfo()->SetSubject ( PdfString("Testing the PoDoFo PDF Library") );
    document.GetInfo()->SetKeywords( PdfString("Test;PDF;Hello World;") );

    /*
     * The last step is to close the document.
     */
    document.Close();
}

int main( int argc, char* argv[] )
{
    const char* filename = "test.pdf";
    /*
     * All podofo functions will throw an exception in case of an error.
     *
     * You should catch the exception to either fix it or report
     * back to the user.
     *
     * All exceptions podofo throws are objects of the class PdfError.
     * Thats why we simply catch PdfError objects.
     */
    try {
        /*
         * Call the drawing routing which will create a PDF file
         * with the filename of the output file as argument.
         */
         HelloWorld( filename );
    } catch( const PdfError & eCode ) {
        /*
         * We have to check if an error has occurred.
         * If yes, we return and print an error message
         * to the commandline.
         */
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }

    /*
     * The PDF was created sucessfully.
     */
    std::cout << std::endl
              << "Created a PDF file containing the line \"Hello World!\": " << filename << std::endl << std::endl;

    return 0;
}