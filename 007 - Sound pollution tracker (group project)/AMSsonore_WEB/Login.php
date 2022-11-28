
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="generator" content="Hugo 0.82.0">
    <title>Ams Sonore</title>

    <link rel="canonical" href="https://getbootstrap.com/docs/5.0/examples/sign-in/">
    <?php 

    $host = "127.0.0.1";
    $user = "root";
    $password = "";
    $db = "ams_sonore";
  
  
    $con = mysqli_connect($host, $user, $password) or die("Couldn't Connect");
    mysqli_select_db($con,$db);
  
    if(isset($_POST['username'])){
      $uname = $_POST['username'];
      $pass = $_POST['password'];
  
      $sql="select * from usertable where userName='".$uname."'";
      
      $result = mysqli_query($con,$sql);
      $rows = $result->fetch_assoc();
      $passwordHashed = $rows['password'];
      //$pass = password_hash("rasmuslerdorf", PASSWORD_DEFAULT, ['cost' => 12]);
      if(mysqli_num_rows($result)==1 && password_verify($pass,$passwordHashed )){
        #header("Location: map.php?user=".$uname );
        header("Location: index.php" );
        exit();
      }
      else{
        echo '<script type="text/javascript">';
        echo 'alert("Wrong login informations")';
        echo '</script>';
  
        echo '<script type="text/javascript">';
        echo 'setTimeout(function() {';
        echo 'window.location.href = "Login.php"';
        echo '}, 1000); // <-- redirect after 1 seconds';
        echo '</script>';
      }
    }
  
  ?>
    

    <!-- Bootstrap core CSS -->
<link href="assets/dist/css/bootstrap.min.css" rel="stylesheet">
    
    <!-- Custom styles for this template -->
    <link href="signin.css" rel="stylesheet">
  </head>
  <body class="text-center">
  
<main class="form-signin">
  <form method="POST" action="#">
    <img class="mb-4" src="hepia.PNG" alt="" width="200" height="100">
    <h1 class="h3 mb-3 fw-normal">AMS Sonore</h1>
    <h2 class="h3 mb-3 fw-normal">Log in</h2>

    <div class="form-floating">
      <input  class="form-control" id="floatingInput" name="username" placeholder="name@example.com">
      <label for="floatingInput">Email address</label>
    </div>
    <div class="form-floating">
      <input type="password" class="form-control"name="password" id="floatingPassword" placeholder="Password">
      <label for="floatingPassword">Password</label>
    </div>

    <div class="checkbox mb-3">
     
    </div>
    <button class="w-100 btn btn-lg btn-primary" type="submit">Sign in</button>
 
  </form>
</main>


    
  </body>
</html>
