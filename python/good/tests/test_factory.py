from flaskr import create_app

# This function tests the configuration of the Flask application. 
# It checks that the default configuration does not enable testing mode (testing is False), 
# and it verifies that when the application is created with a configuration specifying TESTING=True, 
# testing mode is enabled (testing is True).
def test_config():
    assert not create_app().testing
    assert create_app({'TESTING': True}).testing


# test_hello: This function tests the /hello endpoint of the Flask application. 
# It sends a GET request to /hello using the test client (client) and asserts that the response data is 
# equal to b'Hello, World!'.
def test_hello(client):
    response = client.get('/hello')
    assert response.data == b'Hello, World!'