package org.transport.util;

import java.net.URLClassLoader;
import java.net.URL;
import java.io.File;
import java.io.IOException;
import java.util.Properties;

/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
public class DBConnectionConstants {

    private static String userName;
    private static String passWord;
    private static String url;
    private static String driverClass;

    static{
        try {
            Properties props = new Properties();
            props.load(ClassLoader.getSystemClassLoader().getResourceAsStream("org/erms/db/db.properties"));

            userName = props.getProperty("db.username");
            passWord = props.getProperty("db.password");
            url = props.getProperty("db.url");
            driverClass = props.getProperty("db.driverClass");

            System.out.println("userName = " + userName);

        } catch (Exception e) {
            e.printStackTrace();
        }

    }


    public static String getUserName() {
        return userName;
    }

    public static String getPassWord() {
        return passWord;
    }

    public static String getUrl() {
        return url;
    }

    public static String getDriverClass() {
        return driverClass;
    }
}
