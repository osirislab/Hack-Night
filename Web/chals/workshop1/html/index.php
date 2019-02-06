<?php
    session_start();
?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="../../../../favicon.ico">

    <title>SQLi 101</title>

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
            <a class="nav-link" href="index.php">Home <span class="sr-only">(current)</span></a>
          </li>
        </ul>
        <form class="form-inline my-2 my-lg-0" action="login.php">
        <button class="btn btn-outline-success my-2 my-sm-0" type="submit"><?php echo isset($_SESSION['id']) ? "Logout" : "Login" ?></button>
        </form>
      </div>
    </nav>

    <div class="container">
      <div style="padding: 3rem 1.5rem; text-align: center">
        <?php
            if (isset($_SESSION['id'])) {
                echo "<h2>Welcome " . $_SESSION['username'] . "!</h2>";
                echo "<p>" . file_get_contents('/flag.txt') . "</p>";
            } else {
        ?>
        <h1>SQLi</h1>
        <p class="lead">Just log in!</p>
        <?php
            }
        ?>
      </div>

    </div><!-- /.container -->

    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0-beta/js/bootstrap.min.js"></script>
  </body>
</html>

