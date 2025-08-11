<?php
/**
 * Adminer Configuration for Inception Project
 * Auto-fills database connection details from environment variables
 */

function adminer_object() {
    include_once "/var/www/html/adminer.php";
    
    class AdminerSoftware extends Adminer {
        
        function credentials() {
            // Auto-fill with environment variables
            return array(
                getenv('ADMINER_DEFAULT_SERVER') ?: 'mariadb',  // server
                getenv('MARIADB_USER') ?: '',                   // username  
                getenv('MARIADB_PASSWORD') ?: ''                // password
            );
        }
        
        function database() {
            // Auto-select database
            return getenv('MARIADB_DATABASE') ?: '';
        }
        
        function login($login, $password) {
            // Always allow login with correct credentials
            return true;
        }
        
        function loginForm() {
            echo "<table cellspacing='0' class='layout'>\n";
            echo "<tr><th>System<td>" . html_select("auth[driver]", array("server" => "MySQL"), DRIVER, "loginDriver(this);") . "\n";
            echo "<tr><th>Server<td><input name='auth[server]' value='" . h($_ENV['ADMINER_DEFAULT_SERVER'] ?? 'mariadb') . "' title='hostname[:port]' placeholder='localhost' autocapitalize='off'>\n";
            echo "<tr><th>Username<td><input name='auth[username]' id='username' value='" . h($_ENV['MARIADB_USER'] ?? '') . "' autocomplete='username' autocapitalize='off'>\n";
            echo "<tr><th>Password<td><input type='password' name='auth[password]' autocomplete='current-password'>\n";
            echo "<tr><th>Database<td><input name='auth[db]' value='" . h($_ENV['MARIADB_DATABASE'] ?? '') . "' autocapitalize='off'>\n";
            echo "</table>\n";
            echo "<p><input type='submit' value='Login'>\n";
            echo checkbox("auth[permanent]", 1, $_COOKIE["adminer_permanent"], "Permanent login") . "\n";
        }
    }
    
    return new AdminerSoftware;
}

include "/var/www/html/adminer.php";
?>
