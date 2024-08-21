from flask import (
    Blueprint, flash, g, redirect, render_template, request, url_for
) # Imports various functions and classes from the Flask
from werkzeug.exceptions import abort # This imports the abort function from Werkzeug, which allows raising HTTP exceptions.

from flaskr.auth import login_required # Imports auth module of the Flaskr application, which requires users to be logged in to access certain routes.
from flaskr.db import get_db # Imports the get_db function from the db module of the Flaskr application, which retrieves a database connection.

bp = Blueprint('blog', __name__) # Creates a Blueprint named 'blog', which groups related routes and views for managing blog posts.

# This decorates the index function as a route that handles requests to the 
# root URL / for displaying a list of blog posts.
@bp.route('/')
# This function retrieves all blog posts from the database and renders a template to display them.
def index():
    db = get_db()
    posts = db.execute(
        'SELECT p.id, title, body, created, author_id, username'
        ' FROM post p JOIN user u ON p.author_id = u.id'
        ' ORDER BY created DESC'
    ).fetchall()
    return render_template('blog/index.html', posts=posts)



# This decorates the create function as a route that handles both GET and
# POST requests to /create for creating a new blog post.
@bp.route('/create', methods=('GET', 'POST'))
# This decorates the create function with the login_required decorator, 
# ensuring that only authenticated users can create blog posts.
@login_required
# This function handles the creation of a new blog post, validating form input, 
# inserting the post into the database, and redirecting to the index page upon success.
def create():
    if request.method == 'POST':
        title = request.form['title']
        body = request.form['body']
        error = None

        if not title:
            error = 'Title is required.'

        if error is not None:
            flash(error)
        else:
            db = get_db()
            db.execute(
                'INSERT INTO post (title, body, author_id)'
                ' VALUES (?, ?, ?)',
                (title, body, g.user['id'])
            )
            db.commit()
            return redirect(url_for('blog.index'))

    return render_template('blog/create.html')


# This function retrieves a single blog post from the database based on its ID. 
# It also checks whether the current user is the author of the post, if specified.
def get_post(id, check_author=True):
    post = get_db().execute(
        'SELECT p.id, title, body, created, author_id, username'
        ' FROM post p JOIN user u ON p.author_id = u.id'
        ' WHERE p.id = ?',
        (id,)
    ).fetchone()

    if post is None:
        abort(404, f"Post id {id} doesn't exist.")

    if check_author and post['author_id'] != g.user['id']:
        abort(403)

    return post



# This decorates the update function as a route that handles both GET and POST requests to 
# /<int:id>/update for updating an existing blog post.
@bp.route('/<int:id>/update', methods=('GET', 'POST'))
# This decorates the update function with the login_required decorator, 
# ensuring that only authenticated users can update blog posts.
@login_required
# This function handles the updating of an existing blog post, 
# retrieving the post from the database, updating its content, 
# and redirecting to the index page upon success.
def update(id):
    post = get_post(id)

    if request.method == 'POST':
        title = request.form['title']
        body = request.form['body']
        error = None

        if not title:
            error = 'Title is required.'

        if error is not None:
            flash(error)
        else:
            db = get_db()
            db.execute(
                'UPDATE post SET title = ?, body = ?'
                ' WHERE id = ?',
                (title, body, id)
            )
            db.commit()
            return redirect(url_for('blog.index'))

    return render_template('blog/update.html', post=post)


# This decorates the delete function as a route that handles POST requests to 
# /<int:id>/delete for deleting an existing blog post.
@bp.route('/<int:id>/delete', methods=('POST',))
# This decorates the delete function with the login_required decorator, 
# ensuring that only authenticated users can delete blog posts.
@login_required
# This function handles the deletion of an existing blog post from the database and 
# redirects to the index page upon success.
def delete(id):
    get_post(id)
    db = get_db()
    db.execute('DELETE FROM post WHERE id = ?', (id,))
    db.commit()
    return redirect(url_for('blog.index'))