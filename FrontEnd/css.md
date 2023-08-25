CSS 的 position 属性有五个值：static、relative、absolute、fixed 和 sticky。下面是每个值的详细解释：

static：这是元素的默认值。static 定位的元素不受 top、bottom、left、right 属性的影响，它们总是根据文档的正常流动位置。

relative：如果一个元素被设定为 relative，那么它首先会被放置在正常的文档流中，就像它的 position 属性是 static 一样。然后，当你设置 top、right、bottom 或 left 属性时，它会相对于其正常位置进行偏移。值得注意的是，即使它被偏移，它仍然会保留原来在文档流中的空间。另外，一个 position 属性为 relative 的元素会成为其 position 为 absolute 或 fixed 的子元素的定位上下文。

absolute：如前面所述，一个元素的 position 属性被设置为 absolute 时，它会脱离正常的文档流，而且不会保留原来在文档流中的空间。它会相对于最近的非 static 定位的祖先元素进行定位。如果没有这样的祖先元素，那么它将相对于 body 进行定位。你可以通过设置 top、bottom、left、right 属性来指定其位置。

fixed：fixed 定位的元素与 absolute 定位相似，不同之处在于 fixed 定位的元素总是相对于浏览器窗口进行定位，即使页面滚动，它也会保持在同一位置。

sticky：sticky 定位可以看作是 relative 和 fixed 定位的混合。一个 sticky 定位的元素在视口（用户的可见区域）内按照正常文档流进行定位，直到它的 top、right、bottom 或 left 边缘达到定义的偏移距离时，它将“固定”在那个位置，就像 fixed 定位那样，直到它再次滚出视口范围为止。