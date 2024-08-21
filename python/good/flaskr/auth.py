import functools # This imports the functools module, which provides functions for working with higher-order functions.

from flask import (
    Blueprint, flash, g, redirect, render_template, request, session, url_for
) # Imports various functions and classes from the Flask
from werkzeug.security import check_password_hash, generate_password_hash # This imports functions from Werkzeug, a WSGI utility library for Python, used for password hashing and verification.

from flaskr.db import get_db


# This creates a Blueprint named 'auth', which groups related routes and views. 
# The url_prefix parameter specifies that all routes in this blueprint 
# will have /auth prefixed to their URLs.
bp = Blueprint('auth', __name__, url_prefix='/auth')


# This decorates the register function as a route that handles both GET and POST requests to /auth/register.
@bp.route('/register', methods=('GET', 'POST'))
# This function handles user registration. It validates form input, inserts user data into the database, 
# and redirects to the login page upon successful registration.
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        db = get_db()
        error = None

        if not username:
            error = 'Username is required.'
        elif not password:
            error = 'Password is required.'

        if error is None:
            try:
                db.execute(
                    "INSERT INTO user (username, password) VALUES (?, ?)",
                    (username, generate_password_hash(password)),
                )
                db.commit()
            except db.IntegrityError:
                error = f"User {username} is already registered."
            else:
                return redirect(url_for("auth.login"))

        flash(error)

    return render_template('auth/register.html')



# This decorates the login function as a route that handles both GET and POST requests to /auth/login.
@bp.route('/login', methods=('GET', 'POST'))
# This function handles user login. It verifies credentials, 
# sets the user ID in the session upon successful login, and redirects to the index page.
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        db = get_db()
        error = None
        user = db.execute(
            'SELECT * FROM user WHERE username = ?', (username,)
        ).fetchone()

        if user is None:
            error = 'Incorrect username.'
        elif not check_password_hash(user['password'], password):
            error = 'Incorrect password.'

        if error is None:
            session.clear()
            session['user_id'] = user['id']
            return redirect(url_for('index'))

        flash(error)

    return render_template('auth/login.html')

# This registers a function to run before each request, loading the logged-in user from the session
@bp.before_app_request
# This function retrieves the logged-in user's information from the session and stores it in g.user, 
# making it accessible throughout the request.
def load_logged_in_user():
    user_id = session.get('user_id')

    if user_id is None:
        g.user = None
    else:
        g.user = get_db().execute(
            'SELECT * FROM user WHERE id = ?', (user_id,)
        ).fetchone()
        

# This decorates the logout function as a route that handles requests to /auth/logout.
@bp.route('/logout')
# This function clears the session, effectively logging out the user, and redirects to the index page.
def logout():
    session.clear()
    return redirect(url_for('index'))


# This is a decorator function that checks if a user is logged in before allowing access to certain views. 
# If the user is not logged in, it redirects to the login page.
def login_required(view):
    @functools.wraps(view)
    def wrapped_view(**kwargs):
        if g.user is None:
            return redirect(url_for('auth.login'))

        return view(**kwargs)

    return wrapped_view