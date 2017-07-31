<template>
  <div class="Test">
    <h1> {{theHeader}} </h1>
  </div>
</template>

<script>
export default {
  name: 'test',
  data () {
    return {
      theHeader: 'This is the header!'
    }
  }
}
</script>
