<template>

  <div class="CollectData">

    <md-layout md-column>

      <md-layout md-row md-align="left" class="row-with-margin">
        <h3 class="md-title"> Collect Data </h3>
      </md-layout>

    </md-layout>

  </div>

</template>

<script>
export default {
  name: 'CollectData',
  data () {
    return {
      dummy: "dummy",
    }
  }
}
</script>

<style scoped>
.row-with-margin {
  margin-left: 40px;
}
.fixed-width-container {
  width: 250px;
}
</style> 
