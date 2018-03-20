<template>
  <div class="hello">
    <h1>tic tac toe</h1>
    <h2>naughts and crosses, zumo style.</h2>
    
  </div>
</template>

<script>
export default {
  name: 'HelloWorld',
  data() {
    return {
      msg: 'projection.',
    };
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h1 {
  font-weight: normal;
  font-size: 130px;
}
h2 {
  font-weight: normal;
  font-size: 50px;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>
