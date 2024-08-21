import pytest
from flask import g, session
from flaskr.db import get_db


# This function tests the registration process. 
# It checks that accessing the registration page returns a status code of 200, 
# sends a POST request to register a new user, and verifies that the user is redirected to the login page. 
# It also checks the database to ensure that the user is registered.
def test_register(client, app):
    assert client.get('/auth/register').status_code == 200
    response = client.post(
        '/auth/register', data={'username': 'a', 'password': 'a'}
    )
    assert response.headers["Location"] == "/auth/login"

    with app.app_context():
        assert get_db().execute(
            "SELECT * FROM user WHERE username = 'a'",
        ).fetchone() is not None


@pytest.mark.parametrize(('username', 'password', 'message'), (
    ('', '', b'Username is required.'),
    ('a', '', b'Password is required.'),
    ('test', 'test', b'already registered'),
))
# This function tests registration form validation using parameterization.
# It sends POST requests with different combinations of empty and existing usernames and 
# passwords and asserts that the correct error messages are displayed.
def test_register_validate_input(client, username, password, message):
    response = client.post(
        '/auth/register',
        data={'username': username, 'password': password}
    )
    assert message in response.data


# This function tests the login process. It checks that accessing the login page returns a status code of 200, 
# logs in with predefined credentials, and verifies that the user is redirected to the home page. 
# It also checks the session and g object to ensure that the user is logged in.
def test_login(client, auth):
    assert client.get('/auth/login').status_code == 200
    response = auth.login()
    assert response.headers["Location"] == "/"

    with client:
        client.get('/')
        assert session['user_id'] == 1
        assert g.user['username'] == 'test'


@pytest.mark.parametrize(('username', 'password', 'message'), (
    ('a', 'test', b'Incorrect username.'),
    ('test', 'a', b'Incorrect password.'),
))
# This function tests login form validation using parameterization. 
# It sends POST requests with incorrect usernames and passwords and asserts that the correct error
# messages are displayed
def test_login_validate_input(auth, username, password, message):
    response = auth.login(username, password)
    assert message in response.data


# This function tests the logout process. It logs in a user,
#  logs them out, and verifies that the user ID is removed from the session.
def test_logout(client, auth):
    auth.login()

    with client:
        auth.logout()
        assert 'user_id' not in session