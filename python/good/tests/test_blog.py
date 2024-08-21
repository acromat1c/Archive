import pytest
from flaskr.db import get_db

# This function tests the index page, checking that it displays "Log In" and "Register" links for 
# users, and after logging in, it verifies that the "Log Out" link and existing posts are 
# displayed correctly.
def test_index(client, auth):
    response = client.get('/')
    assert b"Log In" in response.data
    assert b"Register" in response.data

    auth.login()
    response = client.get('/')
    assert b'Log Out' in response.data
    assert b'test title' in response.data
    assert b'by test on 2018-01-01' in response.data
    assert b'test\nbody' in response.data
    assert b'href="/1/update"' in response.data
    
@pytest.mark.parametrize('path', (
    '/create',
    '/1/update',
    '/1/delete',
))
# This function tests that certain routes require login by sending POST requests to those routes and
# checking that the response redirects to the login page.
def test_login_required(client, path):
    response = client.post(path)
    assert response.headers["Location"] == "/auth/login"


# This function tests that only the author of a post can modify or delete it. 
# It changes the author of a post to another user and then attempts to modify or 
# delete it with the current user. It verifies that it receives a 403 status code and 
# that the edit link is not visible.
def test_author_required(app, client, auth):
    # change the post author to another user
    with app.app_context():
        db = get_db()
        db.execute('UPDATE post SET author_id = 2 WHERE id = 1')
        db.commit()

    auth.login()
    # current user can't modify other user's post
    assert client.post('/1/update').status_code == 403
    assert client.post('/1/delete').status_code == 403
    # current user doesn't see edit link
    assert b'href="/1/update"' not in client.get('/').data


@pytest.mark.parametrize('path', (
    '/2/update',
    '/2/delete',
))
# This function tests that attempting to modify or delete a non-existent post returns a 404 status code.
def test_exists_required(client, auth, path):
    auth.login()
    assert client.post(path).status_code == 404
    

# This function tests the creation of a new post. 
# It logs in, accesses the creation page, submits a new post, 
# and then checks that the number of posts in the database has increased.
def test_create(client, auth, app):
    auth.login()
    assert client.get('/create').status_code == 200
    client.post('/create', data={'title': 'created', 'body': ''})

    with app.app_context():
        db = get_db()
        count = db.execute('SELECT COUNT(id) FROM post').fetchone()[0]
        assert count == 2


# This function tests updating an existing post. 
# It logs in, accesses the update page for an existing post, submits an updated post, 
# and then checks that the post in the database has been updated accordingly.
def test_update(client, auth, app):
    auth.login()
    assert client.get('/1/update').status_code == 200
    client.post('/1/update', data={'title': 'updated', 'body': ''})

    with app.app_context():
        db = get_db()
        post = db.execute('SELECT * FROM post WHERE id = 1').fetchone()
        assert post['title'] == 'updated'


@pytest.mark.parametrize('path', (
    '/create',
    '/1/update',
))
# This function tests form validation for creating and updating posts by sending POST 
# requests with empty title and body fields and checking that the correct error message is displayed.
def test_create_update_validate(client, auth, path):
    auth.login()
    response = client.post(path, data={'title': '', 'body': ''})
    assert b'Title is required.' in response.data


# This function tests deleting an existing post. 
# It logs in, deletes a post, and then checks that the post no longer exists in the database.
def test_delete(client, auth, app):
    auth.login()
    response = client.post('/1/delete')
    assert response.headers["Location"] == "/"

    with app.app_context():
        db = get_db()
        post = db.execute('SELECT * FROM post WHERE id = 1').fetchone()
        assert post is None