//#include <conio.h>

#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinMessageHandler.h>

SoWinMessageHandler::SoWinMessageHandler( void )
{
    //this->callbackList = new SbList< callbackfunction * >;
    this->processList = new SbList< processEventFunction * >;
}

SoWinMessageHandler::~SoWinMessageHandler( void )
{
    //delete this->callbackList;
    delete this->processList;
}

void SoWinMessageHandler::addProcessEventFunction( processEventFunction * function )
{
    this->processList->append( function );
}

void SoWinMessageHandler::removeProcessEventFunction( processEventFunction * function )
{
    this->processList->removeItem( function );
}

/*
void SoWinMessageHandler::addCB( callbackfunction * function )
{
    this->callbackList->append( function );
}

void SoWinMessageHandler::removeCB( callbackfunction * function )
{
    this->callbackList->removeItem( function );
}*/

void SoWinMessageHandler::messageLoop( void )
{
    MSG msg;
    while(TRUE) {
        if ( PeekMessage( & msg, NULL, 0, 0, PM_NOREMOVE ) ) {
            if ( GetMessage( & msg, NULL, 0, 0 ) ) {
                TranslateMessage( & msg );
                DispatchMessage( & msg );
                processEvent( & msg );
            } else break;   // recieved WM_QUIT
        } else SoWin::doIdleTasks( );
    }
}

void SoWinMessageHandler::processEvent( MSG * msg )
{
    int length = processList->getLength( );
    processEventFunction * const * functions = (processEventFunction * const *) processList->getArrayPtr();
    for( int i = 0; i < length; i++ )
        functions[i]( msg );
}
