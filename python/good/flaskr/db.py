import sqlite3 # imports the SQLite module which is used for working with SQLite databases in Python

import click # click is a Python package for writing custom command line commands

from flask import current_app, g # imports necessary parts from the Flask framework

# g is a special object that is unique for each request.
# it's used to store data that might be needed across 
# different parts of the application during a single request.


# This function is a helper function used to get a connection to the database. 
# It checks if there's already a database connection in the g object. 
# If not, it establishes a new connection to the database configured in the Flask application.
def get_db():
    if 'db' not in g:
        g.db = sqlite3.connect(
            current_app.config['DATABASE'],
            detect_types=sqlite3.PARSE_DECLTYPES
        )
        g.db.row_factory = sqlite3.Row

    return g.db


# This function is a teardown function that closes the database connection. 
# It's registered with Flask's teardown_appcontext function, 
# which means it's called when the application context ends.
def close_db(e=None):
    db = g.pop('db', None)

    if db is not None:
        db.close()
 
        
# This function initializes the database. 
# It gets a database connection using get_db(), 
# reads the schema from a file named schema.sql, 
# and executes the SQL commands in it to create the necessary tables.
def init_db():
    db = get_db()

    with current_app.open_resource('schema.sql') as f:
        db.executescript(f.read().decode('utf8'))


#  This is a decorator provided by Click. 
#  It defines a new command line command named init-db.
# It simply calls init_db() to initialize the database.
@click.command('init-db')
def init_db_command():
    """Clear the existing data and create new tables."""
    init_db()
    click.echo('Initialized the database.')
    

# This function is used to initialize the Flask application with the database functionality.
# It registers the close_db function to be called when the application context ends, 
# and it adds the init-db command to the application's command line interface.
def init_app(app):
    app.teardown_appcontext(close_db)
    app.cli.add_command(init_db_command)