/*
Copyright ©2013 Jontom Xire (JontomXire@yahoo.co.uk). All
Rights Reserved. Permission to use, copy, modify, and distribute this
software and its documentation for educational, research, and
not-for-profit purposes, without fee and without a signed licensing
agreement, is hereby granted, provided that the above copyright notice,
this paragraph and the following two paragraphs appear in all copies,
modifications, and distributions.

IN NO EVENT SHALL JONTOM XIRE BE LIABLE TO ANY PARTY FOR DIRECT,
INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
EVEN IF JONTOM XIRE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.

JONTOM XIRE SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING
DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS".
JONTOM XIRE HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*/

/*
 * This class provides a Darwinet Client to access Darwinet engine
 * functionality. It connects to a Darwinet Server which implements the engine,
 * starting the server if there is not one running already.
 */


#ifndef _DARWINET_CLIENT_HPP_
#define _DARWINET_CLIENT_HPP_


#include <stdbool.h>


class DarwinetClient
{
public:
    DarwinetClient();
    ~DarwinetClient();

    /**
     * @brief Connect to a Darwinet Server.
     *
     * This function will start a Darwinet Server if there is not one
     * currently running in the home directory specified.
     *
     * @param[in]    home_directory   The directory containing the working
     *                                directory of the Darwinet server to
     *                                connect to.
     * @param[in]    username         The username to use when connecting to
     *                                Darwinet.
     * @param[in]    password         The password to use when connecting to
     *                                Darwinet.
     *
     * @retval True if the client successfully connects to the server.
     * @retval False if the client cannot connect to the server.
     */
    bool Connect(const char *home_directory,
                 const char *username,
                 const char *password);
};


#endif /* !_DARWINET_CLIENT_HPP_ */

