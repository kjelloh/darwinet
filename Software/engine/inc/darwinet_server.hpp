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
 * This class implements the Darwinet Server which handles connecting to
 * Darwinet as a node and also handles connecting as a user on behalf of
 * Darwinet Applications, if any are connected using the Darwinet Client class.
 */


#ifndef _DARWINET_SERVER_HPP_
#define _DARWINET_SERVER_HPP_


#include <stdbool.h>


class WorkingDirectory;
class ConfigManager;


class DarwinetServer
{
public:
    /**
     * @brief Spawn a Darwinet Server instance in a new process.
     *
     * This function will spawn a new process to run as a Darwinet Server
     * daemon. The working directory used by the instance will be ".darwinet"
     * in the home directory specified.
     *
     * This function will not spawn a new instance if there is already an
     * instance running using the same working directory. 
     *
     * @param[in]    home_directory   The directory containing the working
     *                                directory of the Darwinet server.
     *
     * @retval True if an instance is running when the function returns.
     * @retval False if no Darwinet Server is running.
     */
    static bool Spawn(const char *home_directory);

private:
    DarwinetServer(WorkingDirectory *dir);
    ~DarwinetServer();

    /**
     * @brief Bind a Darwinet server to its sockets.
     *
     * This function binds a Darwinet server both to its external socket to
     * connect to Darwinet, but also to its internal socket that applications
     * use to communicate with it.
     *
     * On successful exit, the file "server" in the server's working directory
     * will contain the port number of the internal socket.
     *
     * @retval True if all sockets bound successfully.
     * @reval false if an error occurred.
     */
    bool Bind();

    /**
     * @brief Run the Darwinet server.
     *
     * This function runs the Darwinet server until a serious error occurs, the
     * server is requested to stop via the internal socket, or SIGTERM is
     * received.
     */
    void Run();

    /**
     * @brief Stop the Darwinet server.
     */
    void Stop() { _running = false; }

    /**
     * @brief Internal signal handler.
     */
    static void sig_handler(int sig);

    static DarwinetServer *_server;

    WorkingDirectory      *_home;
    ConfigManager         *_config;
    bool                   _running;
    int                    _app_listen_socket;
    uint32_t               _max_app_connections;

};


#endif /* !_DARWINET_SERVER_HPP_ */

