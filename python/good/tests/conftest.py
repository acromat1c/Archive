import os
import tempfile
# Import modules for working with the filesystem and creating temporary files and directories.

import pytest # pytest library, which is used for writing and executing tests in Python.
from flaskr import create_app # This function is presumably used to create instances of the Flask application.
from flaskr.db import get_db, init_db # Imports database-related functions


# This block opens a SQL file named data.sql located in the same directory as 
# the current file (__file__). It reads the contents of the file and stores them in 
# the _data_sql variable.
with open(os.path.join(os.path.dirname(__file__), 'data.sql'), 'rb') as f:
    _data_sql = f.read().decode('utf8')

# This fixture function sets up the Flask application for testing. 
# It creates a temporary database file, initializes the database using init_db(), 
# and populates it with data from _data_sql. After the test is completed, 
# it closes and removes the temporary database file.
@pytest.fixture
def app():
    db_fd, db_path = tempfile.mkstemp()

    app = create_app({
        'TESTING': True,
        'DATABASE': db_path,
    })

    with app.app_context():
        init_db()
        get_db().executescript(_data_sql)

    yield app

    os.close(db_fd)
    os.unlink(db_path)

# This fixture function creates a test client for the Flask application, 
# allowing HTTP requests to be made during testing.
@pytest.fixture
def client(app):
    return app.test_client()


# This fixture function creates a test CLI runner for the Flask application, 
# allowing CLI commands to be executed during testing.
@pytest.fixture
def runner(app):
    return app.test_cli_runner()


# This class defines actions related to user authentication for testing purposes. 
# It includes methods for logging in and logging out a user.
class AuthActions(object):
    def __init__(self, client):
        self._client = client

    def login(self, username='test', password='test'):
        return self._client.post(
            '/auth/login',
            data={'username': username, 'password': password}
        )

    def logout(self):
        return self._client.get('/auth/logout')

# This fixture function creates an instance of AuthActions for testing user authentication.
@pytest.fixture
def auth(client):
    return AuthActions(client)