import sqlite3

import pytest
from flaskr.db import get_db


# This function tests the get_db() and close_db() functions. 
# It ensures that get_db() returns the same database connection within the same application context. 
# It then verifies that attempting to execute a query after closing the database connection raises a 
# ProgrammingError with a message indicating that the connection is closed.
def test_get_close_db(app):
    with app.app_context():
        db = get_db()
        assert db is get_db()

    with pytest.raises(sqlite3.ProgrammingError) as e:
        db.execute('SELECT 1')

    assert 'closed' in str(e.value)
   
# This function tests the init_db_command() function, which is a Click command to initialize the database. 
# It mocks the init_db() function using monkeypatch to set up a fake function that records whether it was
# called. Then, it invokes the init-db command using runner.invoke() and asserts that the command was 
# executed successfully and that the init_db() function was called.
def test_init_db_command(runner, monkeypatch):
    class Recorder(object):
        called = False

    def fake_init_db():
        Recorder.called = True

    monkeypatch.setattr('flaskr.db.init_db', fake_init_db)
    result = runner.invoke(args=['init-db'])
    assert 'Initialized' in result.output
    assert Recorder.called