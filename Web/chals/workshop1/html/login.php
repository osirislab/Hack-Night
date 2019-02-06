<?php
    session_start();
    if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['username']) && isset($_POST['password'])) {
        $db = new mysqli('127.0.0.1', 'php', 'totallyasecurepassword', 'php');
        $username = $_POST['username'];
        $password = sha1($_POST['password']);
        $sql = "SELECT * FROM users WHERE username = '$username' AND password = '$password'";
        if ($_POST['debug']) {
            echo $sql;
        }
        $res = $db->query($sql);
        if ($res && $row = $res->fetch_assoc()) {
            $_SESSION['id'] = $row['id'];
            $_SESSION['username'] = $username;
            header('Location: index.php');
            die();
        } else {
            $error = "No such user!";
        }
    }
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="../../../../favicon.ico">

    <title>Login</title>

    <link href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0-beta/css/bootstrap.min.css" rel="stylesheet">

    <link href="style.css" rel="stylesheet">
  </head>

  <body style="padding-top: 5rem">
    <nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
      <a class="navbar-brand" href="#">SQLi 101</a>
      <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#nav" aria-controls="nav" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>

      <div class="collapse navbar-collapse" id="nav">
        <ul class="navbar-nav mr-auto">
          <li class="nav-item active">
            <a class="nav-link" href="index.php">Home</a>
          </li>
        </ul>
        <form class="form-inline my-2 my-lg-0" action="login.php">
          <button class="btn btn-outline-success my-2 my-sm-0" type="submit">Login</button>
        </form>
      </div>
    </nav>

    <div class="container">
        <form style="margin: 0 auto; width: 300px; text-align: center" method="POST">
            <h2 class="form-signin-heading">Login</h2>
            <?php if (isset($error)) { echo "<h3 style=\"color: red\">$error</h3>"; } ?>
            <input type="hidden" name="debug" value="0">
            <label for="inputusername" class="sr-only">Username</label>
            <input type="username" id="inputusername" name="username" class="form-control" placeholder="Username" required autofocus>
            <label for="inputPassword" class="sr-only">Password</label>
            <input type="password" id="inputPassword" name="password" class="form-control" placeholder="Password" required>
            <br/>
            <button class="btn btn-lg btn-primary btn-block" type="submit">Sign in</button>
        </form>
    </div><!-- /.container -->

    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0-beta/js/bootstrap.min.js"></script>
  </body>
</html>

